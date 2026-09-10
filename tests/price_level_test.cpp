#include <gtest/gtest.h>

#include "matching/price_level.hpp"

using namespace trading;

TEST(PriceLevelTest, InitialState) {
    PriceLevel level{10025};

    EXPECT_EQ(level.price(), 10025);
    EXPECT_TRUE(level.empty());
    EXPECT_EQ(level.size(), 0);
}

TEST(PriceLevelTest, AddAnOrder) {
    PriceLevel level{10025};

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10025,
        .quantity = 100
    };

    level.add_order(order);
    
    EXPECT_FALSE(level.empty());
    EXPECT_EQ(level.size(), 1);
    EXPECT_EQ(level.front().id, 1);
    EXPECT_EQ(level.front().price, 10025);
    EXPECT_EQ(level.front().quantity, 100);
    
}

TEST(PriceLevelTest, RejectsOrderWithWrongPrice) {
    PriceLevel level{10025};

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 9999,
        .quantity = 100
    };

    EXPECT_THROW(level.add_order(order), std::invalid_argument);
}

TEST(PriceLevelTest, MaintainsFIFOOrder) {
    PriceLevel level{10025};

    Order orderA{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10025,
        .quantity = 100
    };
    Order orderB{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10025,
        .quantity = 150
    };
    Order orderC{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10025,
        .quantity = 200
    };

    level.add_order(orderA);
    level.add_order(orderB);
    level.add_order(orderC);
    
    EXPECT_EQ(level.size(), 3);
    EXPECT_EQ(level.front().id, 1);

    level.pop_front();

    EXPECT_EQ(level.size(), 2);
    EXPECT_EQ(level.front().id, 2);

    level.pop_front();

    EXPECT_EQ(level.size(), 1);
    EXPECT_EQ(level.front().id, 3);

    level.pop_front();

    EXPECT_TRUE(level.empty());
    EXPECT_EQ(level.size(), 0);
    
}

TEST(PriceLevelTest, SupportsPartialFill) {
    PriceLevel level{10025};

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10025,
        .quantity = 100
    };

    level.add_order(order);

    level.front().quantity -= 60;

    EXPECT_FALSE(level.empty());
    EXPECT_EQ(level.size(), 1);
    EXPECT_EQ(level.front().id, 1);
    EXPECT_EQ(level.front().quantity, 40);
}

TEST(PriceLevelTest, FullFillsFirstOrderAndPartiallyFillsSecond) {
    PriceLevel level{10025};

    Order orderA{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10025,
        .quantity = 100
    };

    Order orderB{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10025,
        .quantity = 150
    };

    level.add_order(orderA);
    level.add_order(orderB);

    // A fully filled
    level.pop_front();

    // B partially filled by remaining 60
    level.front().quantity -= 60;

    EXPECT_EQ(level.size(), 1);
    EXPECT_EQ(level.front().id, 2);
    EXPECT_EQ(level.front().quantity, 90);
}

TEST(PriceLevelTest, FrontThrowsWhenEmpty) {
    PriceLevel level{10025};

    EXPECT_THROW(level.front(), std::out_of_range);
}

TEST(PriceLevelTest, PopFrontThrowsWhenEmpty) {
    PriceLevel level{10025};

    EXPECT_THROW(level.pop_front(), std::out_of_range);
}