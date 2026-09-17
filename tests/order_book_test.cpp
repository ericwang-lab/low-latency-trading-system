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

TEST(OrderBookTest, RejectsZeroQuantityOrder) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 0
    };

    EXPECT_THROW(
        book.add_order(order),
        std::invalid_argument
    );

    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(OrderBookTest, RejectsZeroPriceLimitOrder) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 0,
        .quantity = 100
    };

    EXPECT_THROW(
        book.add_order(order),
        std::invalid_argument
    );

    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(OrderBookTest, RejectsNegativePriceLimitOrder) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = -100,
        .quantity = 100
    };

    EXPECT_THROW(
        book.add_order(order),
        std::invalid_argument
    );

    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(OrderBookTest, CancelsBuyOrderById) {
    OrderBook book;

    Order order_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    Order order_2{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 200
    };

    book.add_order(order_1);
    book.add_order(order_2);

    EXPECT_TRUE(book.cancel_order(1));

    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 1);

    EXPECT_EQ(level->front().id, 2);
    EXPECT_EQ(level->front().quantity, 200);

    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(OrderBookTest, CancellingLastBuyOrderRemovesPriceLevel) {
    OrderBook book;

    Order order_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 100
    };

    Order order_2{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order_1);
    book.add_order(order_2);

    EXPECT_TRUE(book.cancel_order(1));

    EXPECT_EQ(book.find_bid_level(10200), nullptr);

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 1);
    EXPECT_EQ(level->front().id, 2);
}

TEST(OrderBookTest, CancellingLastSellOrderRemovesPriceLevel) {
    OrderBook book;

    Order order_1{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    Order order_2{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 100
    };

    book.add_order(order_1);
    book.add_order(order_2);

    EXPECT_TRUE(book.cancel_order(1));

    // The empty 10100 price level must be removed.
    EXPECT_EQ(book.find_ask_level(10100), nullptr);

    // 10200 should now become the best ask.
    ASSERT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10200);

    const PriceLevel* level = book.find_ask_level(10200);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 1);
    EXPECT_EQ(level->front().id, 2);

    EXPECT_FALSE(book.best_bid().has_value());
}

TEST(OrderBookTest, CancelNonexistentOrderReturnsFalse) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order);

    EXPECT_FALSE(book.cancel_order(999));

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 1);
    EXPECT_EQ(level->front().id, 1);
    EXPECT_EQ(level->front().quantity, 100);
}

TEST(OrderBookTest, RejectsDuplicateOrderId) {
    OrderBook book;

    Order order_1{
        .id = 42,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    Order order_2{
        .id = 42,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 200
    };

    book.add_order(order_1);

    EXPECT_THROW(
        book.add_order(order_2),
        std::invalid_argument
    );

    // Original order must remain untouched.
    EXPECT_EQ(book.find_bid_level(10200), nullptr);

    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 1);
    EXPECT_EQ(level->front().id, 42);
    EXPECT_EQ(level->front().quantity, 100);

    EXPECT_EQ(book.best_bid().value(), 10100);
}

TEST(OrderBookTest, AllowsReusingOrderIdAfterCancellation) {
    OrderBook book;

    Order original{
        .id = 42,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(original);

    ASSERT_TRUE(book.cancel_order(42));

    Order replacement{
        .id = 42,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 200
    };

    EXPECT_NO_THROW(book.add_order(replacement));

    EXPECT_EQ(book.find_bid_level(10100), nullptr);

    const PriceLevel* level = book.find_bid_level(10200);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 1);
    EXPECT_EQ(level->front().id, 42);
    EXPECT_EQ(level->front().quantity, 200);

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10200);
}
