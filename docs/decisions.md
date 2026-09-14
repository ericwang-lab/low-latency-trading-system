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