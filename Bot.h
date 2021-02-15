#pragma once
#include <iostream>
#include "BotBrain.h"
#include "MerkelMain.h"
#include "ProductData.h"


class Bot: BotBrain {
    public:
        Bot();
        /** initialise all the bot ready to run the symulation */
        void init();
        /** Execute the bot to run throught the simulation */
        void run();


    private:
        /** Format the exchange data so that it can be easily analysed */
        void formatExchangeData(std::map<std::string, std::vector<OrderBookEntry>>& orders);
        void processSale(std::vector<std::string>& sale);
        void initPriceLog(std::vector<std::string> products);

        // private vars
        std::vector<ProductData> priceLog;
        MerkelMain sim = MerkelMain{};

        // Print helper functions
        void printOrders(std::vector<OrderBookEntry> orders, std::string product);
        void printPriceLog();

        bool runBot = true;
        std::string startTime;

};
