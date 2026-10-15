#include <gtest/gtest.h>

#include "matching/small_trade_buffer.hpp"

using namespace trading;

TEST(SmallTradeBufferTest, InitiallyEmpty) {
    SmallTradeBuffer buffer;

    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.size(), 0);
}

TEST(SmallTradeBufferTest, StoresOneTrade) {
    SmallTradeBuffer buffer;

    Trade trade{
        .buy_order_id = 1,
        .sell_order_id = 2,
        .price = 10100,
        .quantity = 50
    };

    buffer.push_back(trade);

    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.size(), 1);

    EXPECT_EQ(buffer[0].buy_order_id, 1);
    EXPECT_EQ(buffer[0].sell_order_id, 2);
    EXPECT_EQ(buffer[0].price, 10100);
    EXPECT_EQ(buffer[0].quantity, 50);
}

TEST(SmallTradeBufferTest, StoresFourTradesInline) {
    SmallTradeBuffer buffer;

    for (OrderId id = 1; id <= 4; ++id) {
        buffer.push_back(Trade{
            .buy_order_id = id,
            .sell_order_id = id + 100,
            .price = 10100,
            .quantity = 50
        });
    }

    EXPECT_EQ(buffer.size(), 4);

    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(buffer[i].buy_order_id, i + 1);
        EXPECT_EQ(buffer[i].sell_order_id, i + 101);
    }
}

TEST(SmallTradeBufferTest, StoresTradesBeyondInlineCapacity) {
    SmallTradeBuffer buffer;

    for (OrderId id = 1; id <= 6; ++id) {
        buffer.push_back(Trade{
            .buy_order_id = id,
            .sell_order_id = id + 100,
            .price = 10100,
            .quantity = 50
        });
    }

    EXPECT_EQ(buffer.size(), 6);

    for (std::size_t i = 0; i < 6; ++i) {
        EXPECT_EQ(buffer[i].buy_order_id, i + 1);
        EXPECT_EQ(buffer[i].sell_order_id, i + 101);
    }
}

TEST(SmallTradeBufferTest, FrontReturnsFirstTrade) {
    SmallTradeBuffer buffer;

    buffer.push_back(Trade{
        .buy_order_id = 1,
        .sell_order_id = 2,
        .price = 10100,
        .quantity = 50
    });

    EXPECT_EQ(buffer.front().buy_order_id, 1);
    EXPECT_EQ(buffer.front().quantity, 50);
}

TEST(SmallTradeBufferTest, FrontThrowsWhenEmpty) {
    SmallTradeBuffer buffer;

    EXPECT_THROW(buffer.front(), std::out_of_range);
}

TEST(SmallTradeBufferTest, IteratesAcrossInlineAndOverflow) {
    SmallTradeBuffer buffer;

    for (OrderId id = 1; id <= 6; ++id) {
        buffer.push_back(Trade{
            .buy_order_id = id,
            .sell_order_id = id + 100,
            .price = 10100,
            .quantity = 50
        });
    }

    OrderId expected_id = 1;

    for (const auto& trade : buffer) {
        EXPECT_EQ(trade.buy_order_id, expected_id);
        ++expected_id;
    }

    EXPECT_EQ(expected_id, 7);
}

TEST(SmallTradeBufferTest, IteratesOverEmptyBuffer) {
    SmallTradeBuffer buffer;

    std::size_t count = 0;

    for (const auto& trade : buffer) {
        (void)trade;
        ++count;
    }

    EXPECT_EQ(count, 0);
}