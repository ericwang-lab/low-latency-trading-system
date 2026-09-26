#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string_view>
#include <vector>

#include "matching/matching_engine.hpp"
#include "matching/order_book.hpp"

namespace {

using Clock = std::chrono::steady_clock;

constexpr std::uint64_t kWarmupIterations = 100'000;
constexpr std::uint64_t kMeasuredIterations = 1'000'000;
constexpr std::size_t kRuns = 10;

using Workload = std::uint64_t (*)(std::uint64_t);

// ------------------------------------------------------------
// Workload 1: RestingLimit + Cancel
// ------------------------------------------------------------

std::uint64_t resting_limit_cancel(std::uint64_t iterations) {
    trading::OrderBook book;
    trading::MatchingEngine engine{book};

    std::uint64_t checksum = 0;

    for (std::uint64_t i = 0; i < iterations; ++i) {
        const trading::OrderId id = i + 1;

        trading::Order order{
            .id = id,
            .side = trading::Side::Buy,
            .type = trading::OrderType::Limit,
            .price = 10000,
            .quantity = 100
        };

        engine.process(order);

        const auto best_bid = book.best_bid();

        if (best_bid.has_value()) {
            checksum += static_cast<std::uint64_t>(*best_bid);
        }

        book.cancel_order(id);
    }

    return checksum;
}

// ------------------------------------------------------------
// Workload 2: RestingSellSetup + FullMatch
// ------------------------------------------------------------

std::uint64_t full_match(std::uint64_t iterations) {
    trading::OrderBook book;
    trading::MatchingEngine engine{book};

    std::uint64_t checksum = 0;

    for (std::uint64_t i = 0; i < iterations; ++i) {
        const trading::OrderId sell_id = (i * 2) + 1;
        const trading::OrderId buy_id = (i * 2) + 2;

        trading::Order resting_sell{
            .id = sell_id,
            .side = trading::Side::Sell,
            .type = trading::OrderType::Limit,
            .price = 10000,
            .quantity = 100
        };

        trading::Order incoming_buy{
            .id = buy_id,
            .side = trading::Side::Buy,
            .type = trading::OrderType::Limit,
            .price = 10000,
            .quantity = 100
        };

        book.add_order(resting_sell);

        auto result = engine.process(incoming_buy);

        checksum +=
            static_cast<std::uint64_t>(result.trades.size());

        if (!result.trades.empty()) {
            checksum +=
                static_cast<std::uint64_t>(
                    result.trades.front().quantity
                );

            checksum +=
                static_cast<std::uint64_t>(
                    result.trades.front().price
                );
        }

        checksum +=
            static_cast<std::uint64_t>(
                result.order.quantity
            );
    }

    return checksum;
}

// ------------------------------------------------------------
// Workload 3: ThreeLevelSetup + MultiLevelSweep
// ------------------------------------------------------------

std::uint64_t multi_level_sweep(std::uint64_t iterations) {
    trading::OrderBook book;
    trading::MatchingEngine engine{book};

    std::uint64_t checksum = 0;

    for (std::uint64_t i = 0; i < iterations; ++i) {
        const trading::OrderId base_id = (i * 4) + 1;

        trading::Order sell_1{
            .id = base_id,
            .side = trading::Side::Sell,
            .type = trading::OrderType::Limit,
            .price = 10000,
            .quantity = 100
        };

        trading::Order sell_2{
            .id = base_id + 1,
            .side = trading::Side::Sell,
            .type = trading::OrderType::Limit,
            .price = 10100,
            .quantity = 100
        };

        trading::Order sell_3{
            .id = base_id + 2,
            .side = trading::Side::Sell,
            .type = trading::OrderType::Limit,
            .price = 10200,
            .quantity = 100
        };

        trading::Order incoming_buy{
            .id = base_id + 3,
            .side = trading::Side::Buy,
            .type = trading::OrderType::Limit,
            .price = 10200,
            .quantity = 300
        };

        book.add_order(sell_1);
        book.add_order(sell_2);
        book.add_order(sell_3);

        auto result = engine.process(incoming_buy);

        checksum +=
            static_cast<std::uint64_t>(result.trades.size());

        for (const auto& trade : result.trades) {
            checksum +=
                static_cast<std::uint64_t>(trade.price);

            checksum +=
                static_cast<std::uint64_t>(trade.quantity);
        }

        checksum +=
            static_cast<std::uint64_t>(
                result.order.quantity
            );
    }

    return checksum;
}

// ------------------------------------------------------------
// Common benchmark runner
// ------------------------------------------------------------

void run_benchmark(
    std::string_view name,
    Workload workload,
    std::uint64_t expected_warmup_checksum,
    std::uint64_t expected_checksum
) {
    const auto warmup_checksum =
        workload(kWarmupIterations);

    std::vector<double> results;
    results.reserve(kRuns);

    std::uint64_t checksum = 0;

    std::cout << "\n=== " << name << " ===\n";

    for (std::size_t run = 0; run < kRuns; ++run) {
        const auto start = Clock::now();

        checksum = workload(kMeasuredIterations);

        const auto end = Clock::now();

        const auto elapsed_ns =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                end - start
            ).count();

        const double ns_per_iteration =
            static_cast<double>(elapsed_ns) /
            static_cast<double>(kMeasuredIterations);

        results.push_back(ns_per_iteration);

        std::cout
            << "Run " << (run + 1)
            << ": " << ns_per_iteration
            << " ns/iteration\n";
    }

    std::sort(results.begin(), results.end());

    double sum = 0.0;

    for (const double result : results) {
        sum += result;
    }

    const double mean =
        sum / static_cast<double>(results.size());

    const double median =
        (results[4] + results[5]) / 2.0;

    std::cout
        << "Min:    "
        << results.front()
        << " ns/iteration\n";

    std::cout
        << "Median: "
        << median
        << " ns/iteration\n";

    std::cout
        << "Mean:   "
        << mean
        << " ns/iteration\n";

    std::cout
        << "Max:    "
        << results.back()
        << " ns/iteration\n";

    std::cout
        << "Warm-up checksum: "
        << warmup_checksum
        << '\n';

    std::cout
        << "Checksum: "
        << checksum
        << '\n';

    if (warmup_checksum != expected_warmup_checksum ||
        checksum != expected_checksum) {
        std::cerr
            << "ERROR: checksum mismatch for "
            << name
            << '\n';
    }
}

} // namespace

int main() {
    std::cout
        << "Warm-up iterations: "
        << kWarmupIterations
        << '\n';

    std::cout
        << "Measured iterations per run: "
        << kMeasuredIterations
        << '\n';

    std::cout
        << "Runs per workload: "
        << kRuns
        << '\n';

    run_benchmark(
        "RestingLimit + Cancel",
        resting_limit_cancel,
        1'000'000'000ULL,
        10'000'000'000ULL
    );

    run_benchmark(
        "RestingSellSetup + FullMatch",
        full_match,
        1'010'100'000ULL,
        10'101'000'000ULL
    );

    run_benchmark(
        "ThreeLevelSetup + MultiLevelSweep",
        multi_level_sweep,
        3'060'300'000ULL,
        30'603'000'000ULL
    );

    return 0;
}