#include <gtest/gtest.h>

#include "matching/order_book.hpp"

using namespace trading;

TEST(OrderBookTest, EmptyBookHasNoBestPrices) {
    OrderBook book;

    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(OrderBookTest, BestBidIsHighestBuyPrice) {
    OrderBook book;
    Order orderA {
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 150
    };
    Order orderB {
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 20100,
        .quantity = 150
    };
    Order orderC {
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 30100,
        .quantity = 150
    };

    book.add_order(orderA);
    book.add_order(orderB);
    book.add_order(orderC);

    EXPECT_FALSE(book.best_ask().has_value());
    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 30100);
}

TEST(OrderBookTest, BestAskIsLowestSellPrice) {
     OrderBook book;
    Order orderA {
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 150
    };
    Order orderB {
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 20100,
        .quantity = 150
    };
    Order orderC {
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 30100,
        .quantity = 150
    };

    book.add_order(orderA);
    book.add_order(orderB);
    book.add_order(orderC);

    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10100);
}

TEST(OrderBookTest, SamePriceBuyOrdersSharePriceLevelAndMaintainFIFO) {
    OrderBook book;

    Order orderA{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 20100,
        .quantity = 100
    };

    Order orderB{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 20100,
        .quantity = 150
    };

    Order orderC{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 20100,
        .quantity = 200
    };

    book.add_order(orderA);
    book.add_order(orderB);
    book.add_order(orderC);

    const PriceLevel* level = book.find_bid_level(20100);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 3);
    EXPECT_EQ(level->front().id, 1);
}

TEST(OrderBookTest, SamePriceSellOrdersSharePriceLevel) {
    OrderBook book;

    Order orderA{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 20100,
        .quantity = 100
    };

    Order orderB{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 20100,
        .quantity = 150
    };

    Order orderC{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 20100,
        .quantity = 200
    };

    book.add_order(orderA);
    book.add_order(orderB);
    book.add_order(orderC);

    const PriceLevel* level = book.find_ask_level(20100);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 3);
    EXPECT_EQ(level->front().id, 1);
}

TEST(OrderBookTest, RejectsMarketOrder) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 100
    };

    EXPECT_THROW(
        book.add_order(order),
        std::invalid_argument
    );
}