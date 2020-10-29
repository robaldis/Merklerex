#pragma once
#include <vector>
#include "OrderBookEntry.h"

class MerkelMain {
    public:
        MerkelMain();
        /** Call this to start up the sim */
        void init();
    private:
        /** print out the options the user can choose from */
        void printMenu ();
        void printHelp();
        void printExchange();
        void enterOffer();
        void enterBid();
        void printWallet();
        void goToNextTimeFrame();
        /** Use cin to get the user input to the menu */
        int getUserOption() ;
        /** take in what number the use has inputed and decide what needs to be run from that */
        void processUserOption(int userOption); 
        void LoadOrderBook();
        
        std::vector<OrderBookEntry> orderBook;
};