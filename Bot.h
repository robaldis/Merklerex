#pragma once
#include <iostream>
#include "BotBrain.h"
#include "MerkelMain.h"


class Bot: BotBrain {
    public:
        Bot();
        void init();
        void printOrders(std::vector<OrderBookEntry> orders);


    private:
        std::vector<ProductData> priceLog;
        MerkelMain sim = MerkelMain{};

};
