add_test([=[OrderTest.StoresLimitBuyOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderTest.StoresLimitBuyOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderTest.StoresLimitBuyOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_test.cpp:7]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderTest.StoresLimitSellOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderTest.StoresLimitSellOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderTest.StoresLimitSellOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_test.cpp:23]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderTest.StoresMarketBuyOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderTest.StoresMarketBuyOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderTest.StoresMarketBuyOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_test.cpp:39]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.InitialState]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.InitialState]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.InitialState]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:7]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.AddAnOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.AddAnOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.AddAnOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:15]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.RejectsOrderWithWrongPrice]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.RejectsOrderWithWrongPrice]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.RejectsOrderWithWrongPrice]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:36]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.MaintainsFIFOOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.MaintainsFIFOOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.MaintainsFIFOOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:50]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.SupportsPartialFill]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.SupportsPartialFill]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.SupportsPartialFill]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:99]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.FullFillsFirstOrderAndPartiallyFillsSecond]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.FullFillsFirstOrderAndPartiallyFillsSecond]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.FullFillsFirstOrderAndPartiallyFillsSecond]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:120]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.FrontThrowsWhenEmpty]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.FrontThrowsWhenEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.FrontThrowsWhenEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:153]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.PopFrontThrowsWhenEmpty]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.PopFrontThrowsWhenEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.PopFrontThrowsWhenEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:159]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.RemovesOrderById]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.RemovesOrderById]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.RemovesOrderById]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:165]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.RemoveNonexistentOrderReturnsFalse]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.RemoveNonexistentOrderReturnsFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.RemoveNonexistentOrderReturnsFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:209]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.RemovingLastOrderLeavesLevelEmpty]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.RemovingLastOrderLeavesLevelEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.RemovingLastOrderLeavesLevelEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:245]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.RemovesOrderByIterator]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.RemovesOrderByIterator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.RemovesOrderByIterator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:264]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.ReportsTotalQuantity]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.ReportsTotalQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.ReportsTotalQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:293]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PriceLevelTest.EmptyLevelHasZeroTotalQuantity]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=PriceLevelTest.EmptyLevelHasZeroTotalQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PriceLevelTest.EmptyLevelHasZeroTotalQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/price_level_test.cpp:327]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.EmptyBookHasNoBestPrices]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.EmptyBookHasNoBestPrices]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.EmptyBookHasNoBestPrices]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:7]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.BestBidIsHighestBuyPrice]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.BestBidIsHighestBuyPrice]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.BestBidIsHighestBuyPrice]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:14]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.BestAskIsLowestSellPrice]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.BestAskIsLowestSellPrice]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.BestAskIsLowestSellPrice]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:47]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.SamePriceBuyOrdersSharePriceLevelAndMaintainFIFO]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.SamePriceBuyOrdersSharePriceLevelAndMaintainFIFO]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.SamePriceBuyOrdersSharePriceLevelAndMaintainFIFO]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:80]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.SamePriceSellOrdersSharePriceLevel]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.SamePriceSellOrdersSharePriceLevel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.SamePriceSellOrdersSharePriceLevel]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:118]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.RejectsMarketOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.RejectsMarketOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.RejectsMarketOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:156]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.RejectsZeroQuantityOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.RejectsZeroQuantityOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.RejectsZeroQuantityOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:173]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.RejectsZeroPriceLimitOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.RejectsZeroPriceLimitOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.RejectsZeroPriceLimitOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:193]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.RejectsNegativePriceLimitOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.RejectsNegativePriceLimitOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.RejectsNegativePriceLimitOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:213]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.CancelsBuyOrderById]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.CancelsBuyOrderById]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.CancelsBuyOrderById]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:233]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.CancellingLastBuyOrderRemovesPriceLevel]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.CancellingLastBuyOrderRemovesPriceLevel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.CancellingLastBuyOrderRemovesPriceLevel]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:271]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.CancellingLastSellOrderRemovesPriceLevel]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.CancellingLastSellOrderRemovesPriceLevel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.CancellingLastSellOrderRemovesPriceLevel]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:307]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.CancelNonexistentOrderReturnsFalse]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.CancelNonexistentOrderReturnsFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.CancelNonexistentOrderReturnsFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:347]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.RejectsDuplicateOrderId]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.RejectsDuplicateOrderId]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.RejectsDuplicateOrderId]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:377]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.AllowsReusingOrderIdAfterCancellation]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.AllowsReusingOrderIdAfterCancellation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.AllowsReusingOrderIdAfterCancellation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:419]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.DecreasingQuantityPreservesPriority]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.DecreasingQuantityPreservesPriority]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.DecreasingQuantityPreservesPriority]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:457]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.IncreasingQuantityLosesPriority]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.IncreasingQuantityLosesPriority]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.IncreasingQuantityLosesPriority]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:524]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ChangingBuyOrderPriceMovesOrderToNewPriceLevel]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ChangingBuyOrderPriceMovesOrderToNewPriceLevel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ChangingBuyOrderPriceMovesOrderToNewPriceLevel]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:591]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ChangingPriceLosesPriorityAtNewPriceLevel]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ChangingPriceLosesPriorityAtNewPriceLevel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ChangingPriceLosesPriorityAtNewPriceLevel]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:646]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ChangingSellOrderPriceLosesPriorityAtNewPriceLevel]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ChangingSellOrderPriceLosesPriorityAtNewPriceLevel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ChangingSellOrderPriceLosesPriorityAtNewPriceLevel]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:720]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.RejectsModifyToZeroQuantity]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.RejectsModifyToZeroQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.RejectsModifyToZeroQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:793]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.RejectsModifyToInvalidPriceWithoutChangingOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.RejectsModifyToInvalidPriceWithoutChangingOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.RejectsModifyToInvalidPriceWithoutChangingOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:831]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ModifyUnknownOrderReturnsFalse]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ModifyUnknownOrderReturnsFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ModifyUnknownOrderReturnsFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:871]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.NoOpModifyPreservesPriority]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.NoOpModifyPreservesPriority]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.NoOpModifyPreservesPriority]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:909]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ReportsBidDepth]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ReportsBidDepth]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ReportsBidDepth]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:977]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.EmptyBookHasEmptyBidDepth]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.EmptyBookHasEmptyBidDepth]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.EmptyBookHasEmptyBidDepth]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1031]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ReportsAskDepth]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ReportsAskDepth]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ReportsAskDepth]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1039]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.EmptyBookHasEmptyAskDepth]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.EmptyBookHasEmptyAskDepth]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.EmptyBookHasEmptyAskDepth]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1093]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.BidDepthUpdatesAfterCancellation]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.BidDepthUpdatesAfterCancellation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.BidDepthUpdatesAfterCancellation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1101]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.BidDepthUpdatesAfterQuantityDecrease]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.BidDepthUpdatesAfterQuantityDecrease]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.BidDepthUpdatesAfterQuantityDecrease]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1145]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.BidDepthUpdatesAfterPriceChange]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.BidDepthUpdatesAfterPriceChange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.BidDepthUpdatesAfterPriceChange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1183]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ReportsTopBidDepthLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ReportsTopBidDepthLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ReportsTopBidDepthLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1224]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ZeroBidDepthLevelsReturnsEmpty]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ZeroBidDepthLevelsReturnsEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ZeroBidDepthLevelsReturnsEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1275]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.BidDepthLimitGreaterThanBookReturnsAllLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.BidDepthLimitGreaterThanBookReturnsAllLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.BidDepthLimitGreaterThanBookReturnsAllLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1293]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ReportsTopAskDepthLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ReportsTopAskDepthLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ReportsTopAskDepthLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1338]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ReportsBookSnapshot]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ReportsBookSnapshot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ReportsBookSnapshot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1389]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.SnapshotRemainsUnchangedAfterBookModification]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.SnapshotRemainsUnchangedAfterBookModification]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.SnapshotRemainsUnchangedAfterBookModification]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1468]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.ValidBookSatisfiesInvariants]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.ValidBookSatisfiesInvariants]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.ValidBookSatisfiesInvariants]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1533]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.InvariantsHoldAfterCancellation]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.InvariantsHoldAfterCancellation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.InvariantsHoldAfterCancellation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1576]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OrderBookTest.InvariantsHoldAfterPriceChangingModification]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=OrderBookTest.InvariantsHoldAfterPriceChangingModification]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OrderBookTest.InvariantsHoldAfterPriceChangingModification]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/order_book_test.cpp:1614]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.BuyOrderPartiallyFillsBestAsk]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.BuyOrderPartiallyFillsBestAsk]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.BuyOrderPartiallyFillsBestAsk]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:9]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.BuyOrderFullyConsumesBestAsk]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.BuyOrderFullyConsumesBestAsk]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.BuyOrderFullyConsumesBestAsk]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:45]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.BuyOrderMatchesMultipleOrdersAtSamePrice]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.BuyOrderMatchesMultipleOrdersAtSamePrice]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.BuyOrderMatchesMultipleOrdersAtSamePrice]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:76]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.SellOrderMatchesMultipleOrdersAtSamePrice]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.SellOrderMatchesMultipleOrdersAtSamePrice]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.SellOrderMatchesMultipleOrdersAtSamePrice]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:131]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.BuyOrderMatchesAcrossMultiplePriceLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.BuyOrderMatchesAcrossMultiplePriceLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.BuyOrderMatchesAcrossMultiplePriceLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:186]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.SellOrderMatchesAcrossMultiplePriceLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.SellOrderMatchesAcrossMultiplePriceLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.SellOrderMatchesAcrossMultiplePriceLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:252]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.UnmatchedBuyOrderRestsInBook]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.UnmatchedBuyOrderRestsInBook]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.UnmatchedBuyOrderRestsInBook]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:318]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.UnmatchedSellOrderRestsInBook]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.UnmatchedSellOrderRestsInBook]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.UnmatchedSellOrderRestsInBook]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:368]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.PartiallyFilledBuyOrderRestsRemainingQuantity]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.PartiallyFilledBuyOrderRestsRemainingQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.PartiallyFilledBuyOrderRestsRemainingQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:421]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.PartiallyFilledSellOrderRestsRemainingQuantity]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.PartiallyFilledSellOrderRestsRemainingQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.PartiallyFilledSellOrderRestsRemainingQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:465]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.BuyBelowBestAskDoesNotMatch]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.BuyBelowBestAskDoesNotMatch]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.BuyBelowBestAskDoesNotMatch]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:509]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.SellAboveBestBidDoesNotMatch]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.SellAboveBestBidDoesNotMatch]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.SellAboveBestBidDoesNotMatch]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:561]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.BuyOrderExactlyConsumesMultipleAskLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.BuyOrderExactlyConsumesMultipleAskLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.BuyOrderExactlyConsumesMultipleAskLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:613]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.SellOrderExactlyConsumesMultipleBidLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.SellOrderExactlyConsumesMultipleBidLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.SellOrderExactlyConsumesMultipleBidLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:673]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.RejectsZeroQuantityOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.RejectsZeroQuantityOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.RejectsZeroQuantityOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:733]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.RejectsInvalidPriceBeforeModifyingBook]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.RejectsInvalidPriceBeforeModifyingBook]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.RejectsInvalidPriceBeforeModifyingBook]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:755]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketBuyConsumesBestAsk]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketBuyConsumesBestAsk]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketBuyConsumesBestAsk]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:794]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketSellConsumesBestBid]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketSellConsumesBestBid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketSellConsumesBestBid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:834]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketBuyDoesNotRestRemainingQuantity]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketBuyDoesNotRestRemainingQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketBuyDoesNotRestRemainingQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:874]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketSellDoesNotRestRemainingQuantity]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketSellDoesNotRestRemainingQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketSellDoesNotRestRemainingQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:907]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketBuyMatchesAcrossMultiplePriceLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketBuyMatchesAcrossMultiplePriceLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketBuyMatchesAcrossMultiplePriceLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:940]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketSellMatchesAcrossMultiplePriceLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketSellMatchesAcrossMultiplePriceLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketSellMatchesAcrossMultiplePriceLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1021]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.ReportsTradeForBuyOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.ReportsTradeForBuyOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.ReportsTradeForBuyOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1102]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.ReportsTradeForSellOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.ReportsTradeForSellOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.ReportsTradeForSellOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1139]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.ReportsMultipleTradesForBuyOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.ReportsMultipleTradesForBuyOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.ReportsMultipleTradesForBuyOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1176]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.ReportsMultipleTradesForSellOrder]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.ReportsMultipleTradesForSellOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.ReportsMultipleTradesForSellOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1239]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.ReportsNoTradesWhenOrderDoesNotMatch]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.ReportsNoTradesWhenOrderDoesNotMatch]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.ReportsNoTradesWhenOrderDoesNotMatch]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1302]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketBuyReportsTradesAtRestingPrices]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketBuyReportsTradesAtRestingPrices]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketBuyReportsTradesAtRestingPrices]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1338]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketSellReportsTradesAtRestingPrices]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketSellReportsTradesAtRestingPrices]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketSellReportsTradesAtRestingPrices]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1387]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketBuyReportsTradesWhenLiquidityIsInsufficient]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketBuyReportsTradesWhenLiquidityIsInsufficient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketBuyReportsTradesWhenLiquidityIsInsufficient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1436]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.MarketSellReportsTradesWhenLiquidityIsInsufficient]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.MarketSellReportsTradesWhenLiquidityIsInsufficient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.MarketSellReportsTradesWhenLiquidityIsInsufficient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1488]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.FullyFilledRestingOrderIsRemovedFromOrderIndex]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.FullyFilledRestingOrderIsRemovedFromOrderIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.FullyFilledRestingOrderIsRemovedFromOrderIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1540]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.FullyFilledRestingOrderIsRemovedFromIndexWhenLevelRemains]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.FullyFilledRestingOrderIsRemovedFromIndexWhenLevelRemains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.FullyFilledRestingOrderIsRemovedFromIndexWhenLevelRemains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1572]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.FullyFilledRestingBuyOrderIsRemovedFromIndexWhenLevelRemains]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.FullyFilledRestingBuyOrderIsRemovedFromIndexWhenLevelRemains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.FullyFilledRestingBuyOrderIsRemovedFromIndexWhenLevelRemains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1621]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.AllowsReusingOrderIdAfterRestingOrderIsFullyFilled]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.AllowsReusingOrderIdAfterRestingOrderIsFullyFilled]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.AllowsReusingOrderIdAfterRestingOrderIsFullyFilled]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1670]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.AskDepthUpdatesAfterPartialFill]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.AskDepthUpdatesAfterPartialFill]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.AskDepthUpdatesAfterPartialFill]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1719]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.AskDepthRemovesLevelAfterFullFill]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.AskDepthRemovesLevelAfterFullFill]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.AskDepthRemovesLevelAfterFullFill]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1767]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.InvariantsHoldAfterPartialFill]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.InvariantsHoldAfterPartialFill]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.InvariantsHoldAfterPartialFill]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1818]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MatchingEngineTest.InvariantsHoldAfterSweepingMultiplePriceLevels]=]  /home/user1/low-latency-trading-system/build-sanitize/matching_tests [==[--gtest_filter=MatchingEngineTest.InvariantsHoldAfterSweepingMultiplePriceLevels]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MatchingEngineTest.InvariantsHoldAfterSweepingMultiplePriceLevels]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/home/user1/low-latency-trading-system/tests/matching_engine_test.cpp:1851]==]
    WORKING_DIRECTORY [==[/home/user1/low-latency-trading-system/build-sanitize]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(matching_tests_TESTS [==[OrderTest.StoresLimitBuyOrder]==] [==[OrderTest.StoresLimitSellOrder]==] [==[OrderTest.StoresMarketBuyOrder]==] [==[PriceLevelTest.InitialState]==] [==[PriceLevelTest.AddAnOrder]==] [==[PriceLevelTest.RejectsOrderWithWrongPrice]==] [==[PriceLevelTest.MaintainsFIFOOrder]==] [==[PriceLevelTest.SupportsPartialFill]==] [==[PriceLevelTest.FullFillsFirstOrderAndPartiallyFillsSecond]==] [==[PriceLevelTest.FrontThrowsWhenEmpty]==] [==[PriceLevelTest.PopFrontThrowsWhenEmpty]==] [==[PriceLevelTest.RemovesOrderById]==] [==[PriceLevelTest.RemoveNonexistentOrderReturnsFalse]==] [==[PriceLevelTest.RemovingLastOrderLeavesLevelEmpty]==] [==[PriceLevelTest.RemovesOrderByIterator]==] [==[PriceLevelTest.ReportsTotalQuantity]==] [==[PriceLevelTest.EmptyLevelHasZeroTotalQuantity]==] [==[OrderBookTest.EmptyBookHasNoBestPrices]==] [==[OrderBookTest.BestBidIsHighestBuyPrice]==] [==[OrderBookTest.BestAskIsLowestSellPrice]==] [==[OrderBookTest.SamePriceBuyOrdersSharePriceLevelAndMaintainFIFO]==] [==[OrderBookTest.SamePriceSellOrdersSharePriceLevel]==] [==[OrderBookTest.RejectsMarketOrder]==] [==[OrderBookTest.RejectsZeroQuantityOrder]==] [==[OrderBookTest.RejectsZeroPriceLimitOrder]==] [==[OrderBookTest.RejectsNegativePriceLimitOrder]==] [==[OrderBookTest.CancelsBuyOrderById]==] [==[OrderBookTest.CancellingLastBuyOrderRemovesPriceLevel]==] [==[OrderBookTest.CancellingLastSellOrderRemovesPriceLevel]==] [==[OrderBookTest.CancelNonexistentOrderReturnsFalse]==] [==[OrderBookTest.RejectsDuplicateOrderId]==] [==[OrderBookTest.AllowsReusingOrderIdAfterCancellation]==] [==[OrderBookTest.DecreasingQuantityPreservesPriority]==] [==[OrderBookTest.IncreasingQuantityLosesPriority]==] [==[OrderBookTest.ChangingBuyOrderPriceMovesOrderToNewPriceLevel]==] [==[OrderBookTest.ChangingPriceLosesPriorityAtNewPriceLevel]==] [==[OrderBookTest.ChangingSellOrderPriceLosesPriorityAtNewPriceLevel]==] [==[OrderBookTest.RejectsModifyToZeroQuantity]==] [==[OrderBookTest.RejectsModifyToInvalidPriceWithoutChangingOrder]==] [==[OrderBookTest.ModifyUnknownOrderReturnsFalse]==] [==[OrderBookTest.NoOpModifyPreservesPriority]==] [==[OrderBookTest.ReportsBidDepth]==] [==[OrderBookTest.EmptyBookHasEmptyBidDepth]==] [==[OrderBookTest.ReportsAskDepth]==] [==[OrderBookTest.EmptyBookHasEmptyAskDepth]==] [==[OrderBookTest.BidDepthUpdatesAfterCancellation]==] [==[OrderBookTest.BidDepthUpdatesAfterQuantityDecrease]==] [==[OrderBookTest.BidDepthUpdatesAfterPriceChange]==] [==[OrderBookTest.ReportsTopBidDepthLevels]==] [==[OrderBookTest.ZeroBidDepthLevelsReturnsEmpty]==] [==[OrderBookTest.BidDepthLimitGreaterThanBookReturnsAllLevels]==] [==[OrderBookTest.ReportsTopAskDepthLevels]==] [==[OrderBookTest.ReportsBookSnapshot]==] [==[OrderBookTest.SnapshotRemainsUnchangedAfterBookModification]==] [==[OrderBookTest.ValidBookSatisfiesInvariants]==] [==[OrderBookTest.InvariantsHoldAfterCancellation]==] [==[OrderBookTest.InvariantsHoldAfterPriceChangingModification]==] [==[MatchingEngineTest.BuyOrderPartiallyFillsBestAsk]==] [==[MatchingEngineTest.BuyOrderFullyConsumesBestAsk]==] [==[MatchingEngineTest.BuyOrderMatchesMultipleOrdersAtSamePrice]==] [==[MatchingEngineTest.SellOrderMatchesMultipleOrdersAtSamePrice]==] [==[MatchingEngineTest.BuyOrderMatchesAcrossMultiplePriceLevels]==] [==[MatchingEngineTest.SellOrderMatchesAcrossMultiplePriceLevels]==] [==[MatchingEngineTest.UnmatchedBuyOrderRestsInBook]==] [==[MatchingEngineTest.UnmatchedSellOrderRestsInBook]==] [==[MatchingEngineTest.PartiallyFilledBuyOrderRestsRemainingQuantity]==] [==[MatchingEngineTest.PartiallyFilledSellOrderRestsRemainingQuantity]==] [==[MatchingEngineTest.BuyBelowBestAskDoesNotMatch]==] [==[MatchingEngineTest.SellAboveBestBidDoesNotMatch]==] [==[MatchingEngineTest.BuyOrderExactlyConsumesMultipleAskLevels]==] [==[MatchingEngineTest.SellOrderExactlyConsumesMultipleBidLevels]==] [==[MatchingEngineTest.RejectsZeroQuantityOrder]==] [==[MatchingEngineTest.RejectsInvalidPriceBeforeModifyingBook]==] [==[MatchingEngineTest.MarketBuyConsumesBestAsk]==] [==[MatchingEngineTest.MarketSellConsumesBestBid]==] [==[MatchingEngineTest.MarketBuyDoesNotRestRemainingQuantity]==] [==[MatchingEngineTest.MarketSellDoesNotRestRemainingQuantity]==] [==[MatchingEngineTest.MarketBuyMatchesAcrossMultiplePriceLevels]==] [==[MatchingEngineTest.MarketSellMatchesAcrossMultiplePriceLevels]==] [==[MatchingEngineTest.ReportsTradeForBuyOrder]==] [==[MatchingEngineTest.ReportsTradeForSellOrder]==] [==[MatchingEngineTest.ReportsMultipleTradesForBuyOrder]==] [==[MatchingEngineTest.ReportsMultipleTradesForSellOrder]==] [==[MatchingEngineTest.ReportsNoTradesWhenOrderDoesNotMatch]==] [==[MatchingEngineTest.MarketBuyReportsTradesAtRestingPrices]==] [==[MatchingEngineTest.MarketSellReportsTradesAtRestingPrices]==] [==[MatchingEngineTest.MarketBuyReportsTradesWhenLiquidityIsInsufficient]==] [==[MatchingEngineTest.MarketSellReportsTradesWhenLiquidityIsInsufficient]==] [==[MatchingEngineTest.FullyFilledRestingOrderIsRemovedFromOrderIndex]==] [==[MatchingEngineTest.FullyFilledRestingOrderIsRemovedFromIndexWhenLevelRemains]==] [==[MatchingEngineTest.FullyFilledRestingBuyOrderIsRemovedFromIndexWhenLevelRemains]==] [==[MatchingEngineTest.AllowsReusingOrderIdAfterRestingOrderIsFullyFilled]==] [==[MatchingEngineTest.AskDepthUpdatesAfterPartialFill]==] [==[MatchingEngineTest.AskDepthRemovesLevelAfterFullFill]==] [==[MatchingEngineTest.InvariantsHoldAfterPartialFill]==] [==[MatchingEngineTest.InvariantsHoldAfterSweepingMultiplePriceLevels]==])
