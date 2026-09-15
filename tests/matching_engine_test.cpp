#include <gtest/gtest.h>

#include "matching/matching_engine.hpp"
#include "matching/process_result.hpp"
#include "matching/trade.hpp"

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

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 0);

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

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 0);

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

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 0);

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

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 0);

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

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 0);

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

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 0);

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

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 60);

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

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 60);

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

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 60);

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

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 60);

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

TEST(MatchingEngineTest, BuyBelowBestAskDoesNotMatch) {
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
        .price = 10099,
        .quantity = 60
    };

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 60);

    // Resting ask should remain unchanged.
    EXPECT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10100);

    const PriceLevel* ask_level =
        book.find_ask_level(10100);

    ASSERT_NE(ask_level, nullptr);
    EXPECT_EQ(ask_level->size(), 1);
    EXPECT_EQ(ask_level->front().id, 1);
    EXPECT_EQ(ask_level->front().quantity, 100);

    // Incoming buy should rest on the bid side.
    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10099);

    const PriceLevel* bid_level =
        book.find_bid_level(10099);

    ASSERT_NE(bid_level, nullptr);
    EXPECT_EQ(bid_level->size(), 1);
    EXPECT_EQ(bid_level->front().id, 2);
    EXPECT_EQ(bid_level->front().quantity, 60);
}

TEST(MatchingEngineTest, SellAboveBestBidDoesNotMatch) {
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
        .price = 10101,
        .quantity = 60
    };

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 60);

    // Resting bid should remain unchanged.
    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    const PriceLevel* bid_level =
        book.find_bid_level(10100);

    ASSERT_NE(bid_level, nullptr);
    EXPECT_EQ(bid_level->size(), 1);
    EXPECT_EQ(bid_level->front().id, 1);
    EXPECT_EQ(bid_level->front().quantity, 100);

    // Incoming sell should rest on the ask side.
    EXPECT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10101);

    const PriceLevel* ask_level =
        book.find_ask_level(10101);

    ASSERT_NE(ask_level, nullptr);
    EXPECT_EQ(ask_level->size(), 1);
    EXPECT_EQ(ask_level->front().id, 2);
    EXPECT_EQ(ask_level->front().quantity, 60);
}

TEST(MatchingEngineTest, BuyOrderExactlyConsumesMultipleAskLevels) {
    OrderBook book;

    Order resting_sell_1{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    Order resting_sell_2{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    Order resting_sell_3{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10101,
        .quantity = 100
    };

    Order resting_sell_4{
        .id = 4,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10102,
        .quantity = 100
    };

    book.add_order(resting_sell_1);
    book.add_order(resting_sell_2);
    book.add_order(resting_sell_3);
    book.add_order(resting_sell_4);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 5,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10102,
        .quantity = 400
    };

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 0);

    EXPECT_FALSE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask_level(), nullptr);

    EXPECT_FALSE(book.best_bid().has_value());
}

TEST(MatchingEngineTest, SellOrderExactlyConsumesMultipleBidLevels) {
    OrderBook book;

    Order resting_buy_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10102,
        .quantity = 100
    };

    Order resting_buy_2{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10102,
        .quantity = 100
    };

    Order resting_buy_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10101,
        .quantity = 100
    };

    Order resting_buy_4{
        .id = 4,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(resting_buy_1);
    book.add_order(resting_buy_2);
    book.add_order(resting_buy_3);
    book.add_order(resting_buy_4);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 5,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 400
    };

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 0);

    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid_level(), nullptr);

    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(MatchingEngineTest, RejectsZeroQuantityOrder) {
    OrderBook book;
    MatchingEngine engine{book};

    Order zero_quantity_order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 0
    };

    EXPECT_THROW(
        engine.process(zero_quantity_order),
        std::invalid_argument
    );

    // Rejecting the order must not modify the book.
    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(MatchingEngineTest, RejectsInvalidPriceBeforeModifyingBook) {
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

    Order invalid_sell{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 0,
        .quantity = 50
    };

    EXPECT_THROW(
        engine.process(invalid_sell),
        std::invalid_argument
    );

    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    EXPECT_EQ(level->size(), 1);
    EXPECT_EQ(level->front().id, 1);
    EXPECT_EQ(level->front().quantity, 100);

    EXPECT_EQ(book.best_bid().value(), 10100);
    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(MatchingEngineTest, MarketBuyConsumesBestAsk) {
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
        .type = OrderType::Market,
        .price = 0,
        .quantity = 60
    };

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 0);

    EXPECT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10100);

    const PriceLevel* ask_level = book.find_ask_level(10100);

    ASSERT_NE(ask_level, nullptr);
    EXPECT_EQ(ask_level->size(), 1);
    EXPECT_EQ(ask_level->front().id, 1);
    EXPECT_EQ(ask_level->front().quantity, 40);

    EXPECT_FALSE(book.best_bid().has_value());
}

TEST(MatchingEngineTest, MarketSellConsumesBestBid) {
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
        .type = OrderType::Market,
        .price = 0,
        .quantity = 60
    };

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 0);

    EXPECT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    const PriceLevel* bid_level = book.find_bid_level(10100);

    ASSERT_NE(bid_level, nullptr);
    EXPECT_EQ(bid_level->size(), 1);
    EXPECT_EQ(bid_level->front().id, 1);
    EXPECT_EQ(bid_level->front().quantity, 40);

    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(MatchingEngineTest, MarketBuyDoesNotRestRemainingQuantity) {
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
        .type = OrderType::Market,
        .price = 0,
        .quantity = 100
    };

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 60);

    EXPECT_FALSE(book.best_ask().has_value());
    EXPECT_FALSE(book.best_bid().has_value());

    EXPECT_EQ(book.find_ask_level(10100), nullptr);
}

TEST(MatchingEngineTest, MarketSellDoesNotRestRemainingQuantity) {
    OrderBook book;

    Order resting_buy{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    book.add_order(resting_buy);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 100
    };

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 60);

    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_FALSE(book.best_ask().has_value());

    EXPECT_EQ(book.find_bid_level(10100), nullptr);
}

TEST(MatchingEngineTest, MarketBuyMatchesAcrossMultiplePriceLevels) {
    OrderBook book;

    Order resting_sell_1{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    Order resting_sell_2{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 30
    };

    Order resting_sell_3{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 50
    };

    Order resting_sell_4{
        .id = 4,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 100
    };

    book.add_order(resting_sell_1);
    book.add_order(resting_sell_2);
    book.add_order(resting_sell_3);
    book.add_order(resting_sell_4);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 5,
        .side = Side::Buy,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 100
    };

    auto result = engine.process(incoming_buy);

    EXPECT_EQ(result.order.quantity, 0);

    // 10100 should be completely consumed.
    EXPECT_EQ(book.find_ask_level(10100), nullptr);

    // 10200 should still contain order #3 with 20 remaining.
    const PriceLevel* level_10200 =
        book.find_ask_level(10200);

    ASSERT_NE(level_10200, nullptr);
    EXPECT_EQ(level_10200->size(), 1);
    EXPECT_EQ(level_10200->front().id, 3);
    EXPECT_EQ(level_10200->front().quantity, 20);

    // 10300 must remain untouched.
    const PriceLevel* level_10300 =
        book.find_ask_level(10300);

    ASSERT_NE(level_10300, nullptr);
    EXPECT_EQ(level_10300->size(), 1);
    EXPECT_EQ(level_10300->front().id, 4);
    EXPECT_EQ(level_10300->front().quantity, 100);

    EXPECT_EQ(book.best_ask().value(), 10200);

    // Fully filled market buy must never rest.
    EXPECT_FALSE(book.best_bid().has_value());
}

TEST(MatchingEngineTest, MarketSellMatchesAcrossMultiplePriceLevels) {
    OrderBook book;

    Order resting_buy_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 40
    };

    Order resting_buy_2{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 30
    };

    Order resting_buy_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 50
    };

    Order resting_buy_4{
        .id = 4,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(resting_buy_1);
    book.add_order(resting_buy_2);
    book.add_order(resting_buy_3);
    book.add_order(resting_buy_4);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 5,
        .side = Side::Sell,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 100
    };

    auto result = engine.process(incoming_sell);

    EXPECT_EQ(result.order.quantity, 0);

    // 10300 should be completely consumed.
    EXPECT_EQ(book.find_bid_level(10300), nullptr);

    // 10200 should still contain order #3 with 20 remaining.
    const PriceLevel* level_10200 =
        book.find_bid_level(10200);

    ASSERT_NE(level_10200, nullptr);
    EXPECT_EQ(level_10200->size(), 1);
    EXPECT_EQ(level_10200->front().id, 3);
    EXPECT_EQ(level_10200->front().quantity, 20);

    // 10100 must remain untouched.
    const PriceLevel* level_10100 =
        book.find_bid_level(10100);

    ASSERT_NE(level_10100, nullptr);
    EXPECT_EQ(level_10100->size(), 1);
    EXPECT_EQ(level_10100->front().id, 4);
    EXPECT_EQ(level_10100->front().quantity, 100);

    EXPECT_EQ(book.best_bid().value(), 10200);

    // Fully filled market sell must never rest.
    EXPECT_FALSE(book.best_ask().has_value());
}

TEST(MatchingEngineTest, ReportsTradeForBuyOrder) {
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
        .price = 10200,
        .quantity = 60
    };

    auto result = engine.process(incoming_buy);

    ASSERT_EQ(result.trades.size(), 1);

    const Trade& trade = result.trades[0];

    EXPECT_EQ(trade.buy_order_id, 2);
    EXPECT_EQ(trade.sell_order_id, 1);
    EXPECT_EQ(trade.price, 10100);
    EXPECT_EQ(trade.quantity, 60);

    EXPECT_EQ(result.order.quantity, 0);
}

TEST(MatchingEngineTest, ReportsTradeForSellOrder) {
    OrderBook book;

    Order resting_buy{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 100
    };

    book.add_order(resting_buy);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 60
    };

    auto result = engine.process(incoming_sell);

    ASSERT_EQ(result.trades.size(), 1);

    const Trade& trade = result.trades[0];

    EXPECT_EQ(trade.buy_order_id, 1);
    EXPECT_EQ(trade.sell_order_id, 2);
    EXPECT_EQ(trade.price, 10200);
    EXPECT_EQ(trade.quantity, 60);

    EXPECT_EQ(result.order.quantity, 0);
}

TEST(MatchingEngineTest, ReportsMultipleTradesForBuyOrder) {
    OrderBook book;

    Order resting_sell_1{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    Order resting_sell_2{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 30
    };

    Order resting_sell_3{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 50
    };

    book.add_order(resting_sell_1);
    book.add_order(resting_sell_2);
    book.add_order(resting_sell_3);

    MatchingEngine engine{book};

    Order incoming_buy{
        .id = 4,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 100
    };

    auto result = engine.process(incoming_buy);

    ASSERT_EQ(result.trades.size(), 3);

    EXPECT_EQ(result.trades[0].buy_order_id, 4);
    EXPECT_EQ(result.trades[0].sell_order_id, 1);
    EXPECT_EQ(result.trades[0].price, 10100);
    EXPECT_EQ(result.trades[0].quantity, 40);

    EXPECT_EQ(result.trades[1].buy_order_id, 4);
    EXPECT_EQ(result.trades[1].sell_order_id, 2);
    EXPECT_EQ(result.trades[1].price, 10100);
    EXPECT_EQ(result.trades[1].quantity, 30);

    EXPECT_EQ(result.trades[2].buy_order_id, 4);
    EXPECT_EQ(result.trades[2].sell_order_id, 3);
    EXPECT_EQ(result.trades[2].price, 10200);
    EXPECT_EQ(result.trades[2].quantity, 30);

    EXPECT_EQ(result.order.quantity, 0);
}

TEST(MatchingEngineTest, ReportsMultipleTradesForSellOrder) {
    OrderBook book;

    Order resting_buy_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 40
    };

    Order resting_buy_2{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 30
    };

    Order resting_buy_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 50
    };

    book.add_order(resting_buy_1);
    book.add_order(resting_buy_2);
    book.add_order(resting_buy_3);

    MatchingEngine engine{book};

    Order incoming_sell{
        .id = 4,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    auto result = engine.process(incoming_sell);

    ASSERT_EQ(result.trades.size(), 3);

    EXPECT_EQ(result.trades[0].buy_order_id, 1);
    EXPECT_EQ(result.trades[0].sell_order_id, 4);
    EXPECT_EQ(result.trades[0].price, 10200);
    EXPECT_EQ(result.trades[0].quantity, 40);

    EXPECT_EQ(result.trades[1].buy_order_id, 2);
    EXPECT_EQ(result.trades[1].sell_order_id, 4);
    EXPECT_EQ(result.trades[1].price, 10200);
    EXPECT_EQ(result.trades[1].quantity, 30);

    EXPECT_EQ(result.trades[2].buy_order_id, 3);
    EXPECT_EQ(result.trades[2].sell_order_id, 4);
    EXPECT_EQ(result.trades[2].price, 10100);
    EXPECT_EQ(result.trades[2].quantity, 30);

    EXPECT_EQ(result.order.quantity, 0);
}

TEST(MatchingEngineTest, ReportsNoTradesWhenOrderDoesNotMatch) {
    OrderBook book;

    Order resting_sell{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
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

    auto result = engine.process(incoming_buy);

    EXPECT_TRUE(result.trades.empty());

    EXPECT_EQ(result.order.quantity, 60);

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    ASSERT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10200);
}

TEST(MatchingEngineTest, MarketBuyReportsTradesAtRestingPrices) {
    OrderBook book;

    Order resting_sell_1{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    Order resting_sell_2{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 50
    };

    book.add_order(resting_sell_1);
    book.add_order(resting_sell_2);

    MatchingEngine engine{book};

    Order market_buy{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 60
    };

    auto result = engine.process(market_buy);

    ASSERT_EQ(result.trades.size(), 2);

    EXPECT_EQ(result.trades[0].buy_order_id, 3);
    EXPECT_EQ(result.trades[0].sell_order_id, 1);
    EXPECT_EQ(result.trades[0].price, 10100);
    EXPECT_EQ(result.trades[0].quantity, 40);

    EXPECT_EQ(result.trades[1].buy_order_id, 3);
    EXPECT_EQ(result.trades[1].sell_order_id, 2);
    EXPECT_EQ(result.trades[1].price, 10200);
    EXPECT_EQ(result.trades[1].quantity, 20);

    EXPECT_EQ(result.order.quantity, 0);
}

TEST(MatchingEngineTest, MarketSellReportsTradesAtRestingPrices) {
    OrderBook book;

    Order resting_buy_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 40
    };

    Order resting_buy_2{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 50
    };

    book.add_order(resting_buy_1);
    book.add_order(resting_buy_2);

    MatchingEngine engine{book};

    Order market_sell{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 60
    };

    auto result = engine.process(market_sell);

    ASSERT_EQ(result.trades.size(), 2);

    EXPECT_EQ(result.trades[0].buy_order_id, 1);
    EXPECT_EQ(result.trades[0].sell_order_id, 3);
    EXPECT_EQ(result.trades[0].price, 10200);
    EXPECT_EQ(result.trades[0].quantity, 40);

    EXPECT_EQ(result.trades[1].buy_order_id, 2);
    EXPECT_EQ(result.trades[1].sell_order_id, 3);
    EXPECT_EQ(result.trades[1].price, 10100);
    EXPECT_EQ(result.trades[1].quantity, 20);

    EXPECT_EQ(result.order.quantity, 0);
}

TEST(MatchingEngineTest, MarketBuyReportsTradesWhenLiquidityIsInsufficient) {
    OrderBook book;

    Order resting_sell_1{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 40
    };

    Order resting_sell_2{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 50
    };

    book.add_order(resting_sell_1);
    book.add_order(resting_sell_2);

    MatchingEngine engine{book};

    Order market_buy{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 150
    };

    auto result = engine.process(market_buy);

    ASSERT_EQ(result.trades.size(), 2);

    EXPECT_EQ(result.trades[0].buy_order_id, 3);
    EXPECT_EQ(result.trades[0].sell_order_id, 1);
    EXPECT_EQ(result.trades[0].price, 10100);
    EXPECT_EQ(result.trades[0].quantity, 40);

    EXPECT_EQ(result.trades[1].buy_order_id, 3);
    EXPECT_EQ(result.trades[1].sell_order_id, 2);
    EXPECT_EQ(result.trades[1].price, 10200);
    EXPECT_EQ(result.trades[1].quantity, 50);

    EXPECT_EQ(result.order.quantity, 60);

    EXPECT_FALSE(book.best_ask().has_value());
    EXPECT_FALSE(book.best_bid().has_value());
}

TEST(MatchingEngineTest, MarketSellReportsTradesWhenLiquidityIsInsufficient) {
    OrderBook book;

    Order resting_buy_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 40
    };

    Order resting_buy_2{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 50
    };

    book.add_order(resting_buy_1);
    book.add_order(resting_buy_2);

    MatchingEngine engine{book};

    Order market_sell{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Market,
        .price = 0,
        .quantity = 150
    };

    auto result = engine.process(market_sell);

    ASSERT_EQ(result.trades.size(), 2);

    EXPECT_EQ(result.trades[0].buy_order_id, 1);
    EXPECT_EQ(result.trades[0].sell_order_id, 3);
    EXPECT_EQ(result.trades[0].price, 10200);
    EXPECT_EQ(result.trades[0].quantity, 40);

    EXPECT_EQ(result.trades[1].buy_order_id, 2);
    EXPECT_EQ(result.trades[1].sell_order_id, 3);
    EXPECT_EQ(result.trades[1].price, 10100);
    EXPECT_EQ(result.trades[1].quantity, 50);

    EXPECT_EQ(result.order.quantity, 60);

    EXPECT_FALSE(book.best_bid().has_value());
    EXPECT_FALSE(book.best_ask().has_value());
}