#pragma once

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>

#include "matching/order.hpp"
#include "matching/price_level.hpp"

namespace trading {

class OrderBook {
public:
    void add_order(const Order& order) {
         if (order.type != OrderType::Limit) {
            throw std::invalid_argument(
                "OrderBook only accepts limit orders"
            );
        }

        if (order.side == Side::Buy) {
            auto result = bids_.try_emplace(
                order.price,
                order.price
            );

            result.first->second.add_order(order);
            return;
        }

        auto result = asks_.try_emplace(
            order.price,
            order.price
        );

        result.first->second.add_order(order);
    }

    const PriceLevel* find_bid_level(Price price) const {
        auto it = bids_.find(price);

        if (it == bids_.end()) {
            return nullptr;
        }

        return &it->second;
    }


    const PriceLevel* find_ask_level(Price price) const {
        auto it = asks_.find(price);

        if (it == asks_.end()) {
            return nullptr;
        }

        return &it->second;
    }

    std::optional<Price> best_bid() const {
        if (bids_.empty()) {
            return std::nullopt;
        }

        return bids_.begin()->first;
    }

    

    std::optional<Price> best_ask() const {
        if (asks_.empty()) {
            return std::nullopt;
        }

        return asks_.begin()->first;
    }


private:
    std::map<Price, PriceLevel, std::greater<Price>> bids_;
    std::map<Price, PriceLevel, std::less<Price>> asks_;
};

} // namespace trading