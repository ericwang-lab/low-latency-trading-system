#pragma once

#include "matching/order.hpp"

namespace trading {

struct Trade {
    OrderId buy_order_id;
    OrderId sell_order_id;
    Price price;
    Quantity quantity;
};

} // namespace trading