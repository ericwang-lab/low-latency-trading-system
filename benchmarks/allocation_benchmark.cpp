
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <new>

#include "matching/matching_engine.hpp"
#include "matching/order_book.hpp"

namespace {

std::atomic<std::uint64_t> allocation_count{0};
std::atomic<std::uint64_t> deallocation_count{0};
std::atomic<bool> measurement_enabled{false};

} // namespace

// ------------------------------------------------------------
// Global allocation hooks
// ------------------------------------------------------------

void* operator new(std::size_t size) {
    if (void* ptr = std::malloc(size)) {
        if (measurement_enabled.load(
                std::memory_order_relaxed)) {
            allocation_count.fetch_add(
                1,
                std::memory_order_relaxed
            );
        }

        return ptr;
    }

    throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept {
    if (ptr != nullptr &&
        measurement_enabled.load(
            std::memory_order_relaxed)) {
        deallocation_count.fetch_add(
            1,
            std::memory_order_relaxed
        );
    }

    std::free(ptr);
}

void operator delete(
    void* ptr,
    std::size_t
) noexcept {
    if (ptr != nullptr &&
        measurement_enabled.load(
            std::memory_order_relaxed)) {
        deallocation_count.fetch_add(
            1,
            std::memory_order_relaxed
        );
    }

    std::free(ptr);
}

// ------------------------------------------------------------
// Measurement utilities
// ------------------------------------------------------------

struct AllocationStats {
    std::uint64_t allocations;
    std::uint64_t deallocations;
};

void begin_measurement() {
    allocation_count.store(
        0,
        std::memory_order_relaxed
    );

    deallocation_count.store(
        0,
        std::memory_order_relaxed
    );

    measurement_enabled.store(
        true,
        std::memory_order_relaxed
    );
}

AllocationStats end_measurement() {
    measurement_enabled.store(
        false,
        std::memory_order_relaxed
    );

    return AllocationStats{
        .allocations = allocation_count.load(
            std::memory_order_relaxed
        ),
        .deallocations = deallocation_count.load(
            std::memory_order_relaxed
        )
    };
}

void print_stats(
    const char* name,
    const AllocationStats& stats
) {
    std::cout << name << '\n';
    std::cout
        << "  Allocations: "
        << stats.allocations
        << '\n';

    std::cout
        << "  Deallocations: "
        << stats.deallocations
        << '\n';
}

// ------------------------------------------------------------
// Workload 1: Insert + Cancel
// ------------------------------------------------------------

bool benchmark_insert_cancel() {
    trading::OrderBook book;

    book.reserve_order_capacity(100);

    trading::Order order{
        .id = 1,
        .side = trading::Side::Buy,
        .type = trading::OrderType::Limit,
        .price = 10000,
        .quantity = 100
    };

    begin_measurement();

    book.add_order(order);

    const AllocationStats insert_stats =
        end_measurement();

    begin_measurement();

    const bool cancelled =
        book.cancel_order(order.id);

    const AllocationStats cancel_stats =
        end_measurement();

    print_stats("Insert:", insert_stats);
    print_stats("Cancel:", cancel_stats);

    const bool valid =
        cancelled &&
        !book.best_bid().has_value() &&
        book.validate_invariants();

    std::cout
        << "Workload valid: "
        << std::boolalpha
        << valid
        << "\n\n";

    return valid;
}

// ------------------------------------------------------------
// Workload 2: Insert + Full Match
// ------------------------------------------------------------

bool benchmark_full_match() {
    trading::OrderBook book;
    trading::MatchingEngine engine{book};

    book.reserve_order_capacity(100);

    trading::Order resting_sell{
        .id = 1,
        .side = trading::Side::Sell,
        .type = trading::OrderType::Limit,
        .price = 10000,
        .quantity = 100
    };

    trading::Order incoming_buy{
        .id = 2,
        .side = trading::Side::Buy,
        .type = trading::OrderType::Limit,
        .price = 10000,
        .quantity = 100
    };

    begin_measurement();

    book.add_order(resting_sell);

    const AllocationStats insert_stats =
        end_measurement();

    begin_measurement();

    auto result = engine.process(incoming_buy);

    const AllocationStats match_stats =
        end_measurement();

    print_stats("Resting sell insert:", insert_stats);
    print_stats("Full match:", match_stats);

    const bool valid =
        result.order.quantity == 0 &&
        result.trades.size() == 1 &&
        result.trades[0].quantity == 100 &&
        result.trades[0].price == 10000 &&
        result.trades[0].buy_order_id == 2 &&
        result.trades[0].sell_order_id == 1 &&
        !book.best_ask().has_value() &&
        !book.best_bid().has_value() &&
        book.validate_invariants();

    std::cout
        << "Workload valid: "
        << std::boolalpha
        << valid
        << "\n\n";

    return valid;
}

bool benchmark_no_match() {
    trading::OrderBook book;
    trading::MatchingEngine engine{book};

    book.reserve_order_capacity(100);

    trading::Order incoming_buy{
        .id = 1,
        .side = trading::Side::Buy,
        .type = trading::OrderType::Limit,
        .price = 10000,
        .quantity = 100
    };

    begin_measurement();

    auto result = engine.process(incoming_buy);

    const AllocationStats stats = end_measurement();

    print_stats("No match:", stats);

    const bool valid =
        result.trades.empty() &&
        result.order.quantity == 100 &&
        book.best_bid() == 10000 &&
        book.validate_invariants();

    std::cout
        << "Workload valid: "
        << std::boolalpha
        << valid
        << "\n\n";

    return valid;
}

// ------------------------------------------------------------
// Main
// ------------------------------------------------------------

int main() {
    std::cout
        << "=== Allocation Benchmark ===\n\n";

    const bool cancel_valid =
        benchmark_insert_cancel();

    const bool match_valid =
        benchmark_full_match();

    if (!cancel_valid || !match_valid) {
        std::cerr
            << "ERROR: Workload validation failed\n";
        return 1;
    }

    const bool no_match_valid = benchmark_no_match();

    return 0;
}
