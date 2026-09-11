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