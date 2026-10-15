#pragma once

#include "matching/small_trade_buffer.hpp"

#include "matching/order.hpp"
#include "matching/trade.hpp"

namespace trading {

struct ProcessResult {
    Order order;
    SmallTradeBuffer trades;
};

} // namespace trading