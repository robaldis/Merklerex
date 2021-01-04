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
        void makeBid(std::string price, std::string amount, std::string product);
        void makeAsk(std::string price, std::string amount, std::string product);
        std::map<std::string,double> getAllAveragePrice();
    private:
        /** print out the options the user can choose from */
        void printMenu ();
        void printHelp();
        void printExchange();
        void enterAsk();
        void enterBid();
        void printWallet();
        void goToNextTimeFrame();
        /** Use cin to get the user input to the menu */
        int getUserOption() ;
        /** take in what number the use has inputed and decide what needs to be run from that */
        void processUserOption(int userOption); 
        
        OrderBook orderBook{"data/test.csv"};
        std::string currentTime;
        Wallet wallet;
};
