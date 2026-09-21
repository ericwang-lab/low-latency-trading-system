# Design Decisions

## Price representation

Prices are represented using signed integers rather than floating-point values.

Example:

10025 may represent €100.25 when the tick unit is one cent.

Reason:

Floating-point values can introduce rounding and equality-comparison issues.

Trade-off:

The system must define an explicit price scale or tick size.

## Price level container

Orders at the same price level are stored in `std::list<Order>`.

Reason:

The first implementation prioritizes correctness and simple FIFO behavior.
`std::list` provides efficient insertion at the back and removal from the
front, and can later support removal of arbitrary orders using iterators.

Trade-off:

`std::list` has poor cache locality and requires node allocations.
It is therefore not assumed to be the final low-latency implementation.
The container choice will be revisited after benchmarking and profiling.


## Price level side ownership

`PriceLevel` does not store or validate the order side.

Reason:

Buy/sell classification belongs to `OrderBook`, which will own the bid and
ask sides. `PriceLevel` is responsible only for maintaining FIFO ordering
for orders at a single price.

Trade-off:

`PriceLevel` trusts its caller to provide orders from the correct side.


## Empty price level access

Calling `front()` or `pop_front()` on an empty `PriceLevel` throws
`std::out_of_range`.

Reason:

The initial implementation prioritizes correctness and makes invalid access
explicit instead of relying on undefined behavior.

Trade-off:

Exception-based checks may not be appropriate for a latency-critical hot
path. This decision will be revisited after profiling and may later be
replaced by caller-enforced preconditions.

## Order book price-level storage

The initial `OrderBook` stores price levels using ordered maps.

Bids use `std::greater<Price>` so that the highest bid is stored at
`begin()`. Asks use `std::less<Price>` so that the lowest ask is stored at
`begin()`.

Reason:

The matching engine needs efficient access to the best bid and best ask.
Using ordered maps keeps price levels sorted automatically and provides
`O(log n)` insertion and lookup while allowing the best price to be accessed
directly from `begin()`.

Trade-off:

`std::map` is a tree-based container with dynamic allocation and pointer
chasing, which may have poor cache locality and may not be suitable for a
latency-critical production order book.

This is a correctness-first implementation. The price-level data structure
will be revisited after benchmarking and profiling.

## Resting orders in the OrderBook

`OrderBook` currently accepts only limit orders.

Market orders are rejected because they should not rest in the book.
They will later be handled by the matching engine, which consumes liquidity
from the opposite side of the book.

Any remaining quantity from an eligible limit order may be added to the
`OrderBook` after matching.

## Matching engine behavior

The matching engine currently supports limit orders using price-time priority.

For incoming buy orders:

- match against the lowest ask first
- the incoming price must be greater than or equal to the ask price

For incoming sell orders:

- match against the highest bid first
- the incoming price must be less than or equal to the bid price

Within the same price level, resting orders are matched in FIFO order.

The matched quantity is:

`min(incoming_quantity, resting_quantity)`

Fully filled resting orders are removed. Empty price levels are also removed
from the order book.

If a limit order still has remaining quantity after all eligible matches are
exhausted, the remainder becomes a resting order in the book.

Trade-off:

The current implementation prioritizes correctness and clarity. Matching,
price-level lookup, container allocation, and branching behavior will be
benchmarked and profiled before introducing low-latency optimizations.

## Market order behavior

The matching engine supports market orders in addition to limit orders.

Market orders do not have a price constraint. They consume available liquidity
starting from the best opposing price and continue across price levels using
price-time priority.

Market orders never become resting orders.

If available liquidity is insufficient, the unmatched quantity is returned by
the matching engine but is not inserted into the order book.

For the current order representation, market orders use `price = 0` because
the price field is not relevant to their execution.

## Order validation

Limit orders must satisfy:

- `price > 0`
- `quantity > 0`

Market orders must satisfy:

- `quantity > 0`

Validation is performed before matching begins so that invalid incoming orders
cannot partially modify the order book before being rejected.

The OrderBook also independently validates orders before allowing them to
become resting orders.

This intentionally duplicates some validation between the MatchingEngine and
OrderBook. Each component maintains its own invariants rather than relying
entirely on its caller.

## Trade result storage

`MatchingEngine::process()` currently stores generated trades in a
`std::vector<Trade>` and returns them as part of `ProcessResult`.

This design was chosen for correctness and API simplicity during the initial
implementation.

A vector may perform dynamic memory allocation when trades are appended.
This is potentially undesirable on a latency-sensitive matching path because
heap allocation can increase both latency and latency variance.

The current implementation intentionally does not optimize this yet.

The project follows:

Correct -> Measure -> Profile -> Optimize -> Measure again

During benchmarking, the cost and frequency of trade-result allocations will
be measured before choosing an alternative representation.

Possible future approaches include:

- reserving expected trade capacity;
- reusing preallocated storage;
- fixed-capacity trade buffers;
- object/memory pools;
- caller-provided output buffers.

Any optimization will be justified by benchmark and profiling results rather
than introduced speculatively.

## Order lookup index and cancellation

Order cancellation initially scanned all price levels and orders to locate an
OrderId. This was correct but required a linear search through the book.

The OrderBook now maintains a secondary index:

    OrderId -> { Side, Price, PriceLevel::OrderIterator }

This allows cancellation to locate the relevant price level and order directly.
With price levels stored in std::map, cancellation is primarily O(log P), where
P is the number of price levels.

PriceLevel uses std::list<Order>, whose iterator stability allows iterators to
resting orders to be stored in the secondary index.

The secondary index introduces an important invariant: whenever a resting order
is removed, its index entry must also be removed.

MatchingEngine previously removed fully filled orders directly from PriceLevel.
After introducing the index, this produced stale iterators and caused undefined
behavior during later cancellation.

Removal responsibility was therefore moved into OrderBook through
remove_best_ask_order() and remove_best_bid_order(). OrderBook now owns
synchronization between:

- price-level storage;
- the OrderId index;
- empty price-level removal.

Duplicate resting OrderIds are rejected to preserve the one-to-one relationship
between resting orders and index entries.

An OrderId may be reused after the previous resting order has left the book,
either through cancellation or a full fill.

## Order modification and priority

Order modification follows price-time priority semantics.

A quantity decrease at the same price is performed in place and preserves
the order's FIFO priority.

A no-op modification (same price and quantity) also preserves priority.

A quantity increase or price change is treated as cancel-and-replace.
The original order is removed and the replacement is inserted at the back
of the appropriate price level, causing it to lose its previous FIFO
priority.

Order modification uses the OrderId index to locate resting orders directly.

All replacement parameters are validated before the OrderBook is mutated.
This prevents an invalid replacement from cancelling the original order
before an exception is raised.

Order references and iterators obtained before cancel_order() must not be
used after cancellation because removal invalidates them.

## Market depth and book snapshots

Market depth is aggregated by price level.

Each DepthLevel contains:
- price
- total resting quantity at that price

Bid depth is returned from best to worst:
highest price to lowest price.

Ask depth is returned from best to worst:
lowest price to highest price.

Top-N depth limits the number of price levels returned,
not the number of individual orders.

PriceLevel::total_quantity() is currently calculated from
the resting orders rather than maintained as cached state.
This keeps orders_ as the single source of truth and avoids
additional synchronization invariants during cancellation,
modification, and matching.

BookSnapshot is a value snapshot containing copies of bid
and ask depth. Changes to the OrderBook after snapshot creation
do not modify previously created snapshots.