#pragma once

#include <cstddef>
#include <list>
#include <stdexcept>
#include <iterator>

#include "matching/order.hpp"

namespace trading {

class PriceLevel {
public:
    using OrderIterator = std::list<Order>::iterator;
    using ConstOrderIterator = std::list<Order>::const_iterator;

    ConstOrderIterator begin() const {
        return orders_.begin();
    }

    ConstOrderIterator end() const {
        return orders_.end();
    }

    explicit PriceLevel(Price price)
        : price_(price) {}

    Price price() const {
        return price_;
    }

    bool empty() const {
        return orders_.empty();
    }

    std::size_t size() const {
        return orders_.size();
    }

    OrderIterator add_order(const Order& order) {
        if (order.price != price_) {
            throw std::invalid_argument(
                "Order price does not match PriceLevel price"
            );
        }

        orders_.push_back(order);

        return std::prev(orders_.end());
    }

    Order& front() {
        if (orders_.empty()) {
            throw std::out_of_range("PriceLevel is empty");
        }
        return orders_.front();
    }

    const Order& front() const {
        if (orders_.empty()) {
            throw std::out_of_range("PriceLevel is empty");
        }
        return orders_.front();
    }

    void pop_front() {
        if (orders_.empty()) {
            throw std::out_of_range("PriceLevel is empty");
        }
        orders_.pop_front();
    }

    void remove_order(OrderIterator it) {
        orders_.erase(it);
    }

    bool remove_order(OrderId id) {
        for (auto it = orders_.begin(); it != orders_.end(); ++it) {
            if (it->id == id) {
                orders_.erase(it);
                return true;
            }
        }

        return false;
    }

private:
    Price price_;
    std::list<Order> orders_;
};

} // namespace trading