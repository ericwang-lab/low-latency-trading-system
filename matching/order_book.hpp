#pragma once

#include <functional>
#include <map>
#include <optional>
#include <stdexcept>
#include <vector>
#include <unordered_map>

#include "matching/order.hpp"
#include "matching/price_level.hpp"

namespace trading {
struct DepthLevel {
    Price price;
    Quantity quantity;
};

struct BookSnapshot {
    std::vector<DepthLevel> bids;
    std::vector<DepthLevel> asks;
};

class OrderBook {
public:

    std::vector<DepthLevel> bid_depth(std::size_t max_levels) const {
        std::vector<DepthLevel> depth;

        for (const auto& [price, level] : bids_) {
            if (depth.size() >= max_levels) {
                break;
            }

            depth.push_back(
                DepthLevel{
                    .price = price,
                    .quantity = level.total_quantity()
                }
            );
        }

        return depth;
    }

    std::vector<DepthLevel> bid_depth() const {
        return bid_depth(bids_.size());
    }

    std::vector<DepthLevel> ask_depth(std::size_t max_levels) const {
        std::vector<DepthLevel> depth;

        for (const auto& [price, level] : asks_) {
            if (depth.size() >= max_levels) {
                break;
            }

            depth.push_back(
                DepthLevel{
                    .price = price,
                    .quantity = level.total_quantity()
                }
            );
        }

        return depth;
    }

    std::vector<DepthLevel> ask_depth() const {
        return ask_depth(asks_.size());
    }

    BookSnapshot snapshot(std::size_t max_levels) const {
        return BookSnapshot{
            .bids = bid_depth(max_levels),
            .asks = ask_depth(max_levels)
        };
    }

    void add_order(const Order& order) {
        if (order.type != OrderType::Limit) {
            throw std::invalid_argument(
                "OrderBook only accepts limit orders"
            );
        }

        if (order.price <= 0) {
            throw std::invalid_argument(
                "Limit order price must be greater than zero"
            );
        }

        if (order.quantity == 0) {
            throw std::invalid_argument(
                "Order quantity must be greater than zero"
            );
        }

        if (order_index_.find(order.id) != order_index_.end()) {
            throw std::invalid_argument(
                "Order id already exists"
            );
        }

        if (order.side == Side::Buy) {
            auto result = bids_.try_emplace(
                order.price,
                order.price
            );

            auto order_it = result.first->second.add_order(order);

            order_index_[order.id] = OrderLocation{
                .side = order.side,
                .price = order.price,
                .order_it = order_it
            };

            return;
        }

        auto result = asks_.try_emplace(
            order.price,
            order.price
        );

        auto order_it = result.first->second.add_order(order);

        order_index_[order.id] = OrderLocation{
            .side = order.side,
            .price = order.price,
            .order_it = order_it
        };
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

    PriceLevel* best_ask_level() {
        if (asks_.empty()) {
            return nullptr;
        }

        return &asks_.begin()->second;
    }

    PriceLevel* best_bid_level() {
        if (bids_.empty()) {
            return nullptr;
        }

        return &bids_.begin()->second;
    }

    bool cancel_order(OrderId id) {
        auto index_it = order_index_.find(id);

        if (index_it == order_index_.end()) {
            return false;
        }

        const Side side = index_it->second.side;
        const Price price = index_it->second.price;
        const auto order_it = index_it->second.order_it;

        if (side == Side::Buy) {
            auto level_it = bids_.find(price);

            if (level_it == bids_.end()) {
                return false;
            }

            PriceLevel& level = level_it->second;

            level.remove_order(order_it);
            order_index_.erase(index_it);

            if (level.empty()) {
                bids_.erase(level_it);
            }

            return true;
        }

        auto level_it = asks_.find(price);

        if (level_it == asks_.end()) {
            return false;
        }

        PriceLevel& level = level_it->second;

        level.remove_order(order_it);
        order_index_.erase(index_it);

        if (level.empty()) {
            asks_.erase(level_it);
        }

        return true;
    }

    void remove_best_ask_order() {
        if (asks_.empty()) {
            return;
        }

        auto level_it = asks_.begin();
        PriceLevel& level = level_it->second;

        if (level.empty()) {
            return;
        }

        const OrderId id = level.front().id;

        order_index_.erase(id);
        level.pop_front();

        if (level.empty()) {
            asks_.erase(level_it);
        }
    }

    void remove_best_bid_order() {
        if (bids_.empty()) {
            return;
        }

        auto level_it = bids_.begin();
        PriceLevel& level = level_it->second;

        if (level.empty()) {
            return;
        }

        const OrderId id = level.front().id;

        order_index_.erase(id);
        level.pop_front();

        if (level.empty()) {
            bids_.erase(level_it);
        }
    }

    bool modify_order(
        OrderId id,
        Price new_price,
        Quantity new_quantity
    ) {
        auto index_it = order_index_.find(id);

        if (index_it == order_index_.end()) {
            return false;
        }

        // Validate everything before modifying the book.
        if (new_price <= 0) {
            throw std::invalid_argument(
                "Limit order price must be greater than zero"
            );
        }

        if (new_quantity == 0) {
            throw std::invalid_argument(
                "Order quantity must be greater than zero"
            );
        }

        OrderLocation& location = index_it->second;
        Order& order = *location.order_it;

        // Same price + quantity decrease:
        // modify in place and preserve FIFO priority.
        if (new_price == order.price &&
            new_quantity < order.quantity) {
            order.quantity = new_quantity;
            return true;
        }

        // Same price + same quantity:
        // no-op, preserve FIFO priority.
        if (new_price == order.price &&
            new_quantity == order.quantity) {
            return true;
        }

        // Quantity increase OR price change:
        // cancel + replace, losing FIFO priority.

        // Copy BEFORE cancel_order(), because cancel invalidates
        // the old iterator/reference.
        Order replacement = order;

        replacement.price = new_price;
        replacement.quantity = new_quantity;

        cancel_order(id);

        add_order(replacement);

        return true;
    }

    bool validate_invariants() const {
        std::size_t resting_order_count = 0;

        // Validate bids.
        for (const auto& [price, level] : bids_) {
            if (level.price() != price) {
                return false;
            }
            if (level.empty()) {
                return false;
            }

            for (auto it = level.begin(); it != level.end(); ++it) {
                const Order& order = *it;

                if (order.side != Side::Buy) {
                    return false;
                }

                if (order.price != price) {
                    return false;
                }

                auto index_it = order_index_.find(order.id);

                if (index_it == order_index_.end()) {
                    return false;
                }

                const OrderLocation& location = index_it->second;

                if (location.side != Side::Buy) {
                    return false;
                }

                if (location.price != price) {
                    return false;
                }

                const Order* indexed_order = &(*location.order_it);

                if (indexed_order != &order) {
                    return false;
                }

                ++resting_order_count;
            }
        }

        // Validate asks.
        for (const auto& [price, level] : asks_) {
            if (level.price() != price) {
                return false;
            }
            if (level.empty()) {
                return false;
            }

            for (auto it = level.begin(); it != level.end(); ++it) {
                const Order& order = *it;

                if (order.side != Side::Sell) {
                    return false;
                }

                if (order.price != price) {
                    return false;
                }

                auto index_it = order_index_.find(order.id);

                if (index_it == order_index_.end()) {
                    return false;
                }

                const OrderLocation& location = index_it->second;

                if (location.side != Side::Sell) {
                    return false;
                }

                if (location.price != price) {
                    return false;
                }

                const Order* indexed_order = &(*location.order_it);

                if (indexed_order != &order) {
                    return false;
                }

                ++resting_order_count;
            }
        }

        // No stale or extra entries may exist in the index.
        if (resting_order_count != order_index_.size()) {
            return false;
        }

        return true;
    }
private:
    std::map<Price, PriceLevel, std::greater<Price>> bids_;
    std::map<Price, PriceLevel, std::less<Price>> asks_;
    struct OrderLocation {
        Side side;
        Price price;
        PriceLevel::OrderIterator order_it;
    };
    std::unordered_map<OrderId, OrderLocation> order_index_;
};

} // namespace trading