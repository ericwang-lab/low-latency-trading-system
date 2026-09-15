#pragma once

#include <vector>

#include "matching/order.hpp"
#include "matching/trade.hpp"

namespace trading {

struct ProcessResult {
    Order order;
    std::vector<Trade> trades;
};

} // namespace trading