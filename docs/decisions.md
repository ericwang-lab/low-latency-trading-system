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