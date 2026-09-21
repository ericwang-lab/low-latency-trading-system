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

TEST(OrderBookTest, ReportsBidDepth) {
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
        .quantity = 250
    };

    Order order_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10050,
        .quantity = 300
    };

    Order order_4{
        .id = 4,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 9900,
        .quantity = 400
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);
    book.add_order(order_4);

    const auto depth = book.bid_depth();

    ASSERT_EQ(depth.size(), 3);

    EXPECT_EQ(depth[0].price, 10100);
    EXPECT_EQ(depth[0].quantity, 350);

    EXPECT_EQ(depth[1].price, 10050);
    EXPECT_EQ(depth[1].quantity, 300);

    EXPECT_EQ(depth[2].price, 9900);
    EXPECT_EQ(depth[2].quantity, 400);
}

TEST(OrderBookTest, EmptyBookHasEmptyBidDepth) {
    OrderBook book;

    const auto depth = book.bid_depth();

    EXPECT_TRUE(depth.empty());
}

TEST(OrderBookTest, ReportsAskDepth) {
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
        .price = 10100,
        .quantity = 250
    };

    Order order_3{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10150,
        .quantity = 300
    };

    Order order_4{
        .id = 4,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 400
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);
    book.add_order(order_4);

    const auto depth = book.ask_depth();

    ASSERT_EQ(depth.size(), 3);

    EXPECT_EQ(depth[0].price, 10100);
    EXPECT_EQ(depth[0].quantity, 350);

    EXPECT_EQ(depth[1].price, 10150);
    EXPECT_EQ(depth[1].quantity, 300);

    EXPECT_EQ(depth[2].price, 10200);
    EXPECT_EQ(depth[2].quantity, 400);
}

TEST(OrderBookTest, EmptyBookHasEmptyAskDepth) {
    OrderBook book;

    const auto depth = book.ask_depth();

    EXPECT_TRUE(depth.empty());
}

TEST(OrderBookTest, BidDepthUpdatesAfterCancellation) {
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
        .quantity = 250
    };

    Order order_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10050,
        .quantity = 300
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);

    ASSERT_TRUE(book.cancel_order(1));

    const auto depth = book.bid_depth();

    ASSERT_EQ(depth.size(), 2);

    EXPECT_EQ(depth[0].price, 10100);
    EXPECT_EQ(depth[0].quantity, 250);

    EXPECT_EQ(depth[1].price, 10050);
    EXPECT_EQ(depth[1].quantity, 300);
}

TEST(OrderBookTest, BidDepthUpdatesAfterQuantityDecrease) {
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
        .quantity = 250
    };

    book.add_order(order_1);
    book.add_order(order_2);

    ASSERT_TRUE(
        book.modify_order(
            1,
            10100,
            50
        )
    );

    const auto depth = book.bid_depth();

    ASSERT_EQ(depth.size(), 1);

    EXPECT_EQ(depth[0].price, 10100);
    EXPECT_EQ(depth[0].quantity, 300);
}

TEST(OrderBookTest, BidDepthUpdatesAfterPriceChange) {
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
        .price = 10050,
        .quantity = 300
    };

    book.add_order(order_1);
    book.add_order(order_2);

    ASSERT_TRUE(
        book.modify_order(
            1,
            10050,
            100
        )
    );

    const auto depth = book.bid_depth();

    ASSERT_EQ(depth.size(), 1);

    EXPECT_EQ(depth[0].price, 10050);
    EXPECT_EQ(depth[0].quantity, 400);

    // The old price level must have disappeared.
    EXPECT_EQ(book.find_bid_level(10100), nullptr);
}

TEST(OrderBookTest, ReportsTopBidDepthLevels) {
    OrderBook book;

    Order order_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10300,
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
        .price = 10100,
        .quantity = 300
    };

    Order order_4{
        .id = 4,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10000,
        .quantity = 400
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);
    book.add_order(order_4);

    const auto depth = book.bid_depth(2);

    ASSERT_EQ(depth.size(), 2);

    EXPECT_EQ(depth[0].price, 10300);
    EXPECT_EQ(depth[0].quantity, 100);

    EXPECT_EQ(depth[1].price, 10200);
    EXPECT_EQ(depth[1].quantity, 200);
}

TEST(OrderBookTest, ZeroBidDepthLevelsReturnsEmpty) {
    OrderBook book;

    Order order{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 100
    };

    book.add_order(order);

    const auto depth = book.bid_depth(0);

    EXPECT_TRUE(depth.empty());
}

TEST(OrderBookTest, BidDepthLimitGreaterThanBookReturnsAllLevels) {
    OrderBook book;

    Order order_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10300,
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
        .price = 10100,
        .quantity = 300
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);

    const auto depth = book.bid_depth(10);

    ASSERT_EQ(depth.size(), 3);

    EXPECT_EQ(depth[0].price, 10300);
    EXPECT_EQ(depth[0].quantity, 100);

    EXPECT_EQ(depth[1].price, 10200);
    EXPECT_EQ(depth[1].quantity, 200);

    EXPECT_EQ(depth[2].price, 10100);
    EXPECT_EQ(depth[2].quantity, 300);
}

TEST(OrderBookTest, ReportsTopAskDepthLevels) {
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
        .quantity = 200
    };

    Order order_3{
        .id = 3,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 300
    };

    Order order_4{
        .id = 4,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10400,
        .quantity = 400
    };

    book.add_order(order_1);
    book.add_order(order_2);
    book.add_order(order_3);
    book.add_order(order_4);

    const auto depth = book.ask_depth(2);

    ASSERT_EQ(depth.size(), 2);

    EXPECT_EQ(depth[0].price, 10100);
    EXPECT_EQ(depth[0].quantity, 100);

    EXPECT_EQ(depth[1].price, 10200);
    EXPECT_EQ(depth[1].quantity, 200);
}

TEST(OrderBookTest, ReportsBookSnapshot) {
    OrderBook book;

    Order bid_1{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10000,
        .quantity = 100
    };

    Order bid_2{
        .id = 2,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 9900,
        .quantity = 200
    };

    Order bid_3{
        .id = 3,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 9800,
        .quantity = 300
    };

    Order ask_1{
        .id = 4,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 400
    };

    Order ask_2{
        .id = 5,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10200,
        .quantity = 500
    };

    Order ask_3{
        .id = 6,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10300,
        .quantity = 600
    };

    book.add_order(bid_1);
    book.add_order(bid_2);
    book.add_order(bid_3);

    book.add_order(ask_1);
    book.add_order(ask_2);
    book.add_order(ask_3);

    const auto snapshot = book.snapshot(2);

    ASSERT_EQ(snapshot.bids.size(), 2);
    ASSERT_EQ(snapshot.asks.size(), 2);

    // Bids: best -> worst.
    EXPECT_EQ(snapshot.bids[0].price, 10000);
    EXPECT_EQ(snapshot.bids[0].quantity, 100);

    EXPECT_EQ(snapshot.bids[1].price, 9900);
    EXPECT_EQ(snapshot.bids[1].quantity, 200);

    // Asks: best -> worst.
    EXPECT_EQ(snapshot.asks[0].price, 10100);
    EXPECT_EQ(snapshot.asks[0].quantity, 400);

    EXPECT_EQ(snapshot.asks[1].price, 10200);
    EXPECT_EQ(snapshot.asks[1].quantity, 500);
}

TEST(OrderBookTest, SnapshotRemainsUnchangedAfterBookModification) {
    OrderBook book;

    Order bid{
        .id = 1,
        .side = Side::Buy,
        .type = OrderType::Limit,
        .price = 10000,
        .quantity = 100
    };

    Order ask{
        .id = 2,
        .side = Side::Sell,
        .type = OrderType::Limit,
        .price = 10100,
        .quantity = 200
    };

    book.add_order(bid);
    book.add_order(ask);

    // Capture the original state.
    const auto snapshot_before = book.snapshot(5);

    ASSERT_EQ(snapshot_before.bids.size(), 1);
    ASSERT_EQ(snapshot_before.asks.size(), 1);

    EXPECT_EQ(snapshot_before.bids[0].price, 10000);
    EXPECT_EQ(snapshot_before.bids[0].quantity, 100);

    EXPECT_EQ(snapshot_before.asks[0].price, 10100);
    EXPECT_EQ(snapshot_before.asks[0].quantity, 200);

    // Modify the actual OrderBook.
    ASSERT_TRUE(
        book.modify_order(
            1,
            10000,
            50
        )
    );

    ASSERT_TRUE(book.cancel_order(2));

    // The old snapshot must remain unchanged.
    ASSERT_EQ(snapshot_before.bids.size(), 1);
    ASSERT_EQ(snapshot_before.asks.size(), 1);

    EXPECT_EQ(snapshot_before.bids[0].price, 10000);
    EXPECT_EQ(snapshot_before.bids[0].quantity, 100);

    EXPECT_EQ(snapshot_before.asks[0].price, 10100);
    EXPECT_EQ(snapshot_before.asks[0].quantity, 200);

    // A new snapshot must reflect the current OrderBook.
    const auto snapshot_after = book.snapshot(5);

    ASSERT_EQ(snapshot_after.bids.size(), 1);
    EXPECT_TRUE(snapshot_after.asks.empty());

    EXPECT_EQ(snapshot_after.bids[0].price, 10000);
    EXPECT_EQ(snapshot_after.bids[0].quantity, 50);
}