#pragma once

#include <array>
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <iterator>

#include "matching/trade.hpp"

namespace trading {

class SmallTradeBuffer {
public:
    static constexpr std::size_t kInlineCapacity = 4;
    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Trade;
        using difference_type = std::ptrdiff_t;
        using pointer = const Trade*;
        using reference = const Trade&;

        const_iterator(
            const SmallTradeBuffer* buffer,
            std::size_t index
        )
            : buffer_(buffer),
            index_(index) {}

        reference operator*() const {
            return (*buffer_)[index_];
        }

        pointer operator->() const {
            return &(*buffer_)[index_];
        }

        const_iterator& operator++() {
            ++index_;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator previous = *this;
            ++(*this);
            return previous;
        }

        bool operator==(const const_iterator& other) const {
            return buffer_ == other.buffer_ &&
                index_ == other.index_;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }

    private:
        const SmallTradeBuffer* buffer_;
        std::size_t index_;
    };

    const_iterator begin() const {
        return const_iterator{this, 0};
    }

    const_iterator end() const {
        return const_iterator{this, size_};
    }

    bool empty() const {
        return size_ == 0;
    }

    std::size_t size() const {
        return size_;
    }

    void push_back(const Trade& trade) {
        if (size_ < kInlineCapacity) {
            inline_trades_[size_] = trade;
        } else {
            overflow_trades_.push_back(trade);
        }

        ++size_;
    }

    const Trade& operator[](std::size_t index) const {
        if (index < kInlineCapacity) {
            return inline_trades_[index];
        }

        return overflow_trades_[index - kInlineCapacity];
    }
    
    const Trade& front() const {
        if (empty()) {
            throw std::out_of_range("SmallTradeBuffer is empty");
        }

        return (*this)[0];
    }
private:
    std::array<Trade, kInlineCapacity> inline_trades_{};
    std::vector<Trade> overflow_trades_;
    std::size_t size_ = 0;
};

} // namespace trading