#pragma once

#include <cstddef>
#include <list>
#include <stdexcept>

#include "matching/order.hpp"

namespace trading {

class PriceLevel {
public:
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

    void add_order(const Order& order) {
        if (order.price != price_) {
            throw std::invalid_argument("Order price does not match price level");
        }
        orders_.push_back(order);
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

private:
    Price price_;
    std::list<Order> orders_;
};

} // namespace trading