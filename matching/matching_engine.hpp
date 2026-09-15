#pragma once

#include <algorithm>
#include <stdexcept>
#include <utility>

#include "matching/order.hpp"
#include "matching/order_book.hpp"
#include "matching/process_result.hpp"

namespace trading {

class MatchingEngine {
public:
    explicit MatchingEngine(OrderBook& book)
        : book_(book) {}

    ProcessResult process(Order order) {
        if (order.type == OrderType::Limit && order.price <= 0) {
            throw std::invalid_argument(
                "Limit order price must be greater than zero"
            );
        }

        if (order.quantity == 0) {
            throw std::invalid_argument(
                "Order quantity must be greater than zero"
            );
        }

        std::vector<Trade> trades;

        if (order.side == Side::Buy) {
           while (order.quantity > 0) {
                PriceLevel* level = book_.best_ask_level();

                // No sell liquidity available.
                if (level == nullptr) {
                    break;
                }

                // Buy price is lower than best ask -> no crossing.
                if ( order.type == OrderType::Limit && order.price < level->price()) {
                    break;
                }

                Order& resting = level->front();

                const Quantity matched_quantity =
                    std::min(order.quantity, resting.quantity);

                trades.push_back(Trade{
                    .buy_order_id = order.id,
                    .sell_order_id = resting.id,
                    .price = resting.price,
                    .quantity = matched_quantity
                });

                order.quantity -= matched_quantity;
                resting.quantity -= matched_quantity;

                if (resting.quantity == 0) {
                    level->pop_front();

                    if (level->empty()) {
                        book_.remove_best_ask_level();
                    }
                }
            }

            if (order.type == OrderType::Limit && order.quantity > 0) {
                book_.add_order(order);
            }

            return ProcessResult{
                .order = order,
                .trades = std::move(trades)
            };
        }

        while (order.quantity > 0) {
            PriceLevel* level = book_.best_bid_level();

            // No buy liquidity available.
            if (level == nullptr) {
                break;
            }

            // Sell price is higher than best bid -> no crossing.
            if (order.type == OrderType::Limit && order.price > level->price()) {
                break;
            }

            Order& resting = level->front();

            const Quantity matched_quantity =
                std::min(order.quantity, resting.quantity);

            trades.push_back(Trade{
                .buy_order_id = resting.id,
                .sell_order_id = order.id,
                .price = resting.price,
                .quantity = matched_quantity
            });

            order.quantity -= matched_quantity;
            resting.quantity -= matched_quantity;

            if (resting.quantity == 0) {
                level->pop_front();
                if (level->empty()) {
                    book_.remove_best_bid_level();
                }
            }
        }

        if (order.type == OrderType::Limit && order.quantity > 0) {
            book_.add_order(order);
        }

        return ProcessResult{
            .order = order,
            .trades = std::move(trades)
        };
    }

private:
    OrderBook& book_;
};

} // namespace trading