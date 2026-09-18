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

TEST(OrderBookTest, DecreasingQuantityPreservesPriority) {
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
        .quantity = 100
    };

    Order order_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);

    ASSERT_TRUE(
        book.modify_order(
            2,
            10100,
            50
        )
    );

    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    ASSERT_EQ(level->size(), 3);

    auto it = level->begin();

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 2);
    EXPECT_EQ(it->quantity, 50);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 3);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    EXPECT_EQ(it, level->end());
}

TEST(OrderBookTest, IncreasingQuantityLosesPriority) {
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
        .quantity = 100
    };

    Order order_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);

    ASSERT_TRUE(
        book.modify_order(
            2,
            10100,
            200
        )
    );

    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    ASSERT_EQ(level->size(), 3);

    auto it = level->begin();

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 3);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 2);
    EXPECT_EQ(it->quantity, 200);

    ++it;

    EXPECT_EQ(it, level->end());
}

TEST(OrderBookTest, ChangingBuyOrderPriceMovesOrderToNewPriceLevel) {
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
        .quantity = 100
    };

    book.add_order(order_1);
    book.add_order(order_2);

    ASSERT_TRUE(
        book.modify_order(
            1,
            10200,
            100
        )
    );

    // #1 must have moved to 10200.
    const PriceLevel* new_level = book.find_bid_level(10200);

    ASSERT_NE(new_level, nullptr);
    ASSERT_EQ(new_level->size(), 1);

    EXPECT_EQ(new_level->front().id, 1);
    EXPECT_EQ(new_level->front().price, 10200);
    EXPECT_EQ(new_level->front().quantity, 100);

    // #2 must remain at 10100.
    const PriceLevel* old_level = book.find_bid_level(10100);

    ASSERT_NE(old_level, nullptr);
    ASSERT_EQ(old_level->size(), 1);

    EXPECT_EQ(old_level->front().id, 2);
    EXPECT_EQ(old_level->front().price, 10100);
    EXPECT_EQ(old_level->front().quantity, 100);

    // 10200 is now the best bid.
    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10200);
}

TEST(OrderBookTest, ChangingPriceLosesPriorityAtNewPriceLevel) {
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
        .price = 10200,
        .quantity = 200
    };

    Order order_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 300
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);

    ASSERT_TRUE(
        book.modify_order(
            1,
            10200,
            100
        )
    );

    // The old price level should disappear because #1
    // was its only order.
    EXPECT_EQ(book.find_bid_level(10100), nullptr);

    const PriceLevel* level = book.find_bid_level(10200);

    ASSERT_NE(level, nullptr);
    ASSERT_EQ(level->size(), 3);

    auto it = level->begin();

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 2);
    EXPECT_EQ(it->quantity, 200);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 3);
    EXPECT_EQ(it->quantity, 300);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    EXPECT_EQ(it, level->end());

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10200);
}

TEST(OrderBookTest, ChangingSellOrderPriceLosesPriorityAtNewPriceLevel) {
    OrderBook book;

    Order order_1{
        .id = 1,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 100
    };

    Order order_2{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 200
    };

    Order order_3{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 300
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);

    ASSERT_TRUE(
        book.modify_order(
            1,
            10200,
            100
        )
    );

    // #1 was the only order at 10300, so the old level disappears.
    EXPECT_EQ(book.find_ask_level(10300), nullptr);

    const PriceLevel* level = book.find_ask_level(10200);

    ASSERT_NE(level, nullptr);
    ASSERT_EQ(level->size(), 3);

    auto it = level->begin();

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 2);
    EXPECT_EQ(it->quantity, 200);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 3);
    EXPECT_EQ(it->quantity, 300);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    EXPECT_EQ(it, level->end());

    ASSERT_TRUE(book.best_ask().has_value());
    EXPECT_EQ(book.best_ask().value(), 10200);
}

TEST(OrderBookTest, RejectsModifyToZeroQuantity) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order);

    EXPECT_THROW(
        book.modify_order(
            1,
            10100,
            0
        ),
        std::invalid_argument
    );

    // Failed modification must not change the existing order.
    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    ASSERT_EQ(level->size(), 1);

    EXPECT_EQ(level->front().id, 1);
    EXPECT_EQ(level->front().price, 10100);
    EXPECT_EQ(level->front().quantity, 100);

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);
}

TEST(OrderBookTest, RejectsModifyToInvalidPriceWithoutChangingOrder) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order);

    EXPECT_THROW(
        book.modify_order(
            1,
            0,
            100
        ),
        std::invalid_argument
    );

    // Failed modification must leave the original order untouched.
    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    ASSERT_EQ(level->size(), 1);

    EXPECT_EQ(level->front().id, 1);
    EXPECT_EQ(level->front().price, 10100);
    EXPECT_EQ(level->front().quantity, 100);

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    // The invalid price level must never have been created.
    EXPECT_EQ(book.find_bid_level(0), nullptr);
}

TEST(OrderBookTest, ModifyUnknownOrderReturnsFalse) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order);

    EXPECT_FALSE(
        book.modify_order(
            999,
            10200,
            200
        )
    );

    // Existing order must remain completely unchanged.
    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    ASSERT_EQ(level->size(), 1);

    EXPECT_EQ(level->front().id, 1);
    EXPECT_EQ(level->front().price, 10100);
    EXPECT_EQ(level->front().quantity, 100);

    ASSERT_TRUE(book.best_bid().has_value());
    EXPECT_EQ(book.best_bid().value(), 10100);

    // No new price level should have been created.
    EXPECT_EQ(book.find_bid_level(10200), nullptr);
}

TEST(OrderBookTest, NoOpModifyPreservesPriority) {
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
        .quantity = 100
    };

    Order order_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);

    // Same price + same quantity = no-op.
    ASSERT_TRUE(
        book.modify_order(
            2,
            10100,
            100
        )
    );

    const PriceLevel* level = book.find_bid_level(10100);

    ASSERT_NE(level, nullptr);
    ASSERT_EQ(level->size(), 3);

    auto it = level->begin();

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 2);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    ASSERT_NE(it, level->end());
    EXPECT_EQ(it->id, 3);
    EXPECT_EQ(it->quantity, 100);

    ++it;

    EXPECT_EQ(it, level->end());
}