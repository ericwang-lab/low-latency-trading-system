#include <gtest/gtest.h>

#include "matching/order.hpp"

using namespace trading;

TEST(OrderTest, StoresLimitBuyOrder) {
    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10025,
        .quantity = 200
    };

    EXPECT_EQ(order.id, 1);
    EXPECT_EQ(order.side, Side::Buy);
    EXPECT_EQ(order.type, OrderType::Limit);
    EXPECT_EQ(order.price, 10025);
    EXPECT_EQ(order.quantity, 200);
}

TEST(OrderTest, StoresLimitSellOrder) {
    Order order{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 150
    };

    EXPECT_EQ(order.id, 2);
    EXPECT_EQ(order.side, Side::Sell);
    EXPECT_EQ(order.type, OrderType::Limit);
    EXPECT_EQ(order.price, 10100);
    EXPECT_EQ(order.quantity, 150);
}

TEST(OrderTest, StoresMarketBuyOrder) {
    Order order{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 50
    };

    EXPECT_EQ(order.type, OrderType::Market);
    EXPECT_EQ(order.price, 0);
    EXPECT_EQ(order.quantity, 50);
}