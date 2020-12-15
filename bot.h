#pragma once
#include "OrderBookEntry.h"
#include <string>
#include "MerkelMain.h"

class Bot {
    public:
        Bot();
        /** initialise the bot */
        void init();

    private:
        /** Make a bid on the market with the amount*/
        void makeBid(std::string amount, std::string price, OrderBookType orderType);
        /** Make an ask on the market with the amount*/
        void makeAsk(std::string amount, std::string price, OrderBookType orderType);


        MerkelMain sim;

};
