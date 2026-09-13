#pragma once

#include <algorithm>
#include <stdexcept>

#include "matching/order.hpp"
#include "matching/order_book.hpp"

namespace trading {

class MatchingEngine {
public:
    explicit MatchingEngine(OrderBook& book)
        : book_(book) {}

    Order process(Order order) {
        if (order.type != OrderType::Limit) {
            throw std::invalid_argument(
                "MatchingEngine currently only supports limit orders"
            );
        }

        if (order.side == Side::Buy) {
           while (order.quantity > 0) {
                PriceLevel* level = book_.best_ask_level();

                // No sell liquidity available.
                if (level == nullptr) {
                    break;
                }

                // Buy price is lower than best ask -> no crossing.
                if (order.price < level->price()) {
                    break;
                }

                Order& resting = level->front();

                const Quantity matched_quantity =
                    std::min(order.quantity, resting.quantity);

                order.quantity -= matched_quantity;
                resting.quantity -= matched_quantity;

                if (resting.quantity == 0) {
                    level->pop_front();

                    if (level->empty()) {
                        book_.remove_best_ask_level();
                    }
                }
            }

            if (order.quantity > 0) {
                book_.add_order(order);
            }

            return order;
        }

        while (order.quantity > 0) {
            PriceLevel* level = book_.best_bid_level();

            // No buy liquidity available.
            if (level == nullptr) {
                break;
            }

            // Sell price is higher than best bid -> no crossing.
            if (order.price > level->price()) {
                break;
            }

            Order& resting = level->front();

            const Quantity matched_quantity =
                std::min(order.quantity, resting.quantity);

            order.quantity -= matched_quantity;
            resting.quantity -= matched_quantity;

            if (resting.quantity == 0) {
                level->pop_front();
                if (level->empty()) {
                    book_.remove_best_bid_level();
                }
            }
        }

        if (order.quantity > 0) {
            book_.add_order(order);
        }

        return order;
    }

private:
    OrderBook& book_;
};

} // namespace trading