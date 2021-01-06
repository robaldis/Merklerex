#pragma once
#include <iostream>
#include "BotBrain.h"
#include "MerkelMain.h"
#include "ProductData.h"


class Bot: BotBrain {
    public:
        Bot();
        void init();


    private:
        /** Format the exchange data so that it can be easily analysed */
        void formatExchangeData(std::map<std::string, std::vector<OrderBookEntry>> orders);
        void initPriceLog(std::vector<std::string> products);

        // private vars
        std::vector<ProductData> priceLog;
        MerkelMain sim = MerkelMain{};

        // Print helper functions
        void printOrders(std::vector<OrderBookEntry> orders, std::string product);
        void printPriceLog();

};
