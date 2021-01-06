#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain {
    public:
        MerkelMain();
        /** Call this to start up the sim */
        void init(bool bot=false);
        std::vector<OrderBookEntry> getExchangeData();
        void makeAsk(std::string amount, std::string price, std::string product);
        void makeBid(std::string amount, std::string price, std::string product);
        void goToNextTimeFrame();
    private:
        /** print out the options the user can choose from */
        void printMenu ();
        void printHelp();
        void printExchange();
        void enterAsk();
        void enterBid();
        void printWallet();
        /** Use cin to get the user input to the menu */
        int getUserOption() ;
        /** take in what number the use has inputed and decide what 
         * needs to be run from that */
        void processUserOption(int userOption); 
        
        OrderBook orderBook{"data/test.csv"};
        std::string currentTime;
        Wallet wallet;
};
