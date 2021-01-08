#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "Log.h"

class MerkelMain {
    public:
        MerkelMain();
        /** Call this to start up the sim */
        void init(bool bot=false);
        std::map<std::string, std::vector<OrderBookEntry>> getExchangeData();
        std::vector<std::string> getKnownProducts();
        void makeAsk(std::string amount, std::string price, std::string product);
        void makeBid(std::string amount, std::string price, std::string product);
        void goToNextTimeFrame();
        void printExchange();
    private:
        /** print out the options the user can choose from */
        void printMenu ();
        void printHelp();
        void enterAsk();
        void enterBid();
        void printWallet();
        /** Use cin to get the user input to the menu */
        int getUserOption() ;
        /** take in what number the use has inputed and decide what 
         * needs to be run from that */
        void processUserOption(int userOption); 
        std::string startTime;
        
        OrderBook orderBook{"data/book_data.csv"};
        std::string currentTime;
        Wallet wallet;
        Log log;
        int count = 0;
};
