#pragma once

#include <cstdint>

namespace trading {

using OrderId = std::uint64_t;
using Price = std::int64_t;
using Quantity = std::uint32_t;

enum class Side {
    Buy,
    Sell
};

enum class OrderType {
    Limit,
    Market
};

struct Order {
    OrderId id;
    Side side;
    OrderType type;
    Price price;
    Quantity quantity; // for now, it's remaining quantity
};

} // namespace trading