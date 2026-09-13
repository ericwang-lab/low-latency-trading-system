#include <gtest/gtest.h>

#include "matching/matching_engine.hpp"

using namespace trading;

TEST(MatchingEngineTest, BuyOrderPartiallyFillsBestAsk) {
    OrderBook book;

    Order resting_sell{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(resting_sell);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 60
    };

    Order result = engine.process(incoming_buy);

    EXPECT_EQ(result.quantity, 0);

    PriceLevel* ask_level = book.best_ask_level();

    ASSERT_NE(ask_level, nullptr);
    EXPECT_EQ(ask_level->price(), 10100);
    EXPECT_EQ(ask_level->size(), 1);
    EXPECT_EQ(ask_level->front().id, 1);
    EXPECT_EQ(ask_level->front().quantity, 40);
}

TEST(MatchingEngineTest, BuyOrderFullyConsumesBestAsk) {
    OrderBook book;

    Order resting_sell{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(resting_sell);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    Order result = engine.process(incoming_buy);

    EXPECT_EQ(result.quantity, 0);

    EXPECT_FALSE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask_level(), nullptr);
}

TEST(MatchingEngineTest, BuyOrderMatchesMultipleOrdersAtSamePrice) {
    OrderBook book;

    Order resting_sell_a{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    Order resting_sell_b{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 30
    };

    Order resting_sell_c{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(resting_sell_a);
    book.add_order(resting_sell_b);
    book.add_order(resting_sell_c);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 4,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    Order result = engine.process(incoming_buy);

    EXPECT_EQ(result.quantity, 0);

    PriceLevel* ask_level = book.best_ask_level();

    ASSERT_NE(ask_level, nullptr);
    EXPECT_EQ(ask_level->price(), 10100);
    EXPECT_EQ(ask_level->size(), 1);

    EXPECT_EQ(ask_level->front().id, 3);
    EXPECT_EQ(ask_level->front().quantity, 70);
}

TEST(MatchingEngineTest, SellOrderMatchesMultipleOrdersAtSamePrice) {
    OrderBook book;

    Order resting_buy_a{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    Order resting_buy_b{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 30
    };

    Order resting_buy_c{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(resting_buy_a);
    book.add_order(resting_buy_b);
    book.add_order(resting_buy_c);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 4,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    Order result = engine.process(incoming_sell);

    EXPECT_EQ(result.quantity, 0);

    PriceLevel* bid_level = book.best_bid_level();

    ASSERT_NE(bid_level, nullptr);
    EXPECT_EQ(bid_level->price(), 10100);
    EXPECT_EQ(bid_level->size(), 1);

    EXPECT_EQ(bid_level->front().id, 3);
    EXPECT_EQ(bid_level->front().quantity, 70);
}

TEST(MatchingEngineTest, BuyOrderMatchesAcrossMultiplePriceLevels) {
    OrderBook book;

    Order resting_sell_a{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    Order resting_sell_b{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 30
    };

    Order resting_sell_c{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 100
    };

    book.add_order(resting_sell_a);
    book.add_order(resting_sell_b);
    book.add_order(resting_sell_c);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 4,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 60
    };

    Order result = engine.process(incoming_buy);

    EXPECT_EQ(result.quantity, 0);

    EXPECT_FALSE(book.find_ask_level(10100) != nullptr);

    const PriceLevel* level_10200 =
        book.find_ask_level(10200);

    ASSERT_NE(level_10200, nullptr);
    EXPECT_EQ(level_10200->size(), 1);
    EXPECT_EQ(level_10200->front().id, 2);
    EXPECT_EQ(level_10200->front().quantity, 10);

    const PriceLevel* level_10300 =
        book.find_ask_level(10300);

    ASSERT_NE(level_10300, nullptr);
    EXPECT_EQ(level_10300->front().id, 3);
    EXPECT_EQ(level_10300->front().quantity, 100);

    EXPECT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10200);
}

TEST(MatchingEngineTest, SellOrderMatchesAcrossMultiplePriceLevels) {
    OrderBook book;

    Order resting_buy_a{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 40
    };

    Order resting_buy_b{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 30
    };

    Order resting_buy_c{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(resting_buy_a);
    book.add_order(resting_buy_b);
    book.add_order(resting_buy_c);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 4,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 60
    };

    Order result = engine.process(incoming_sell);

    EXPECT_EQ(result.quantity, 0);

    EXPECT_EQ(book.find_bid_level(10300), nullptr);

    const PriceLevel* level_10200 =
        book.find_bid_level(10200);

    ASSERT_NE(level_10200, nullptr);
    EXPECT_EQ(level_10200->size(), 1);
    EXPECT_EQ(level_10200->front().id, 2);
    EXPECT_EQ(level_10200->front().quantity, 10);

    const PriceLevel* level_10100 =
        book.find_bid_level(10100);

    ASSERT_NE(level_10100, nullptr);
    EXPECT_EQ(level_10100->front().id, 3);
    EXPECT_EQ(level_10100->front().quantity, 100);

    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10200);
}

TEST(MatchingEngineTest, UnmatchedBuyOrderRestsInBook) {
    OrderBook book;

    Order resting_sell{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 100
    };

    book.add_order(resting_sell);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 60
    };

    Order result = engine.process(incoming_buy);

    EXPECT_EQ(result.quantity, 60);

    EXPECT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10300);

    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10200);

    const PriceLevel* bid_level =
        book.find_bid_level(10200);

    ASSERT_NE(bid_level, nullptr);
    EXPECT_EQ(bid_level->size(), 1);
    EXPECT_EQ(bid_level->front().id, 2);
    EXPECT_EQ(bid_level->front().quantity, 60);

    const PriceLevel* ask_level =
        book.find_ask_level(10300);

    ASSERT_NE(ask_level, nullptr);
    EXPECT_EQ(ask_level->size(), 1);
    EXPECT_EQ(ask_level->front().id, 1);
    EXPECT_EQ(ask_level->front().quantity, 100);
}

TEST(MatchingEngineTest, UnmatchedSellOrderRestsInBook) {
    OrderBook book;

    Order resting_buy{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(resting_buy);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 60
    };

    Order result = engine.process(incoming_sell);

    EXPECT_EQ(result.quantity, 60);

    // Original bid should remain unchanged.
    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    // Incoming sell should now rest on the ask side.
    EXPECT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10200);

    const PriceLevel* ask_level =
        book.find_ask_level(10200);

    ASSERT_NE(ask_level, nullptr);
    EXPECT_EQ(ask_level->size(), 1);
    EXPECT_EQ(ask_level->front().id, 2);
    EXPECT_EQ(ask_level->front().quantity, 60);

    // Original resting buy must not have been modified.
    const PriceLevel* bid_level =
        book.find_bid_level(10100);

    ASSERT_NE(bid_level, nullptr);
    EXPECT_EQ(bid_level->size(), 1);
    EXPECT_EQ(bid_level->front().id, 1);
    EXPECT_EQ(bid_level->front().quantity, 100);
}

TEST(MatchingEngineTest, PartiallyFilledBuyOrderRestsRemainingQuantity) {
    OrderBook book;

    Order resting_sell{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    book.add_order(resting_sell);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 100
    };

    Order result = engine.process(incoming_buy);

    EXPECT_EQ(result.quantity, 60);

    // The resting sell was fully consumed.
    EXPECT_FALSE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask_level(), nullptr);

    // The remaining incoming buy should rest in the book.
    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10200);

    const PriceLevel* bid_level =
        book.find_bid_level(10200);

    ASSERT_NE(bid_level, nullptr);
    EXPECT_EQ(bid_level->size(), 1);
    EXPECT_EQ(bid_level->front().id, 2);
    EXPECT_EQ(bid_level->front().quantity, 60);
}

TEST(MatchingEngineTest, PartiallyFilledSellOrderRestsRemainingQuantity) {
    OrderBook book;

    Order resting_buy{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 40
    };

    book.add_order(resting_buy);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 100
    };

    Order result = engine.process(incoming_sell);

    EXPECT_EQ(result.quantity, 60);

    // The resting buy was fully consumed.
    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid_level(), nullptr);

    // The remaining incoming sell should rest in the book.
    EXPECT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10200);

    const PriceLevel* ask_level =
        book.find_ask_level(10200);

    ASSERT_NE(ask_level, nullptr);
    EXPECT_EQ(ask_level->size(), 1);
    EXPECT_EQ(ask_level->front().id, 2);
    EXPECT_EQ(ask_level->front().quantity, 60);
}