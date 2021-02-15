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
        /** returns a map of <product, OrderBookEntry> for the current timestamp
         * the exchange is in */
        std::map<std::string, std::vector<OrderBookEntry>> getExchangeData();
        /** Get all the known products that are used in the simulation */
        std::vector<std::string> getKnownProducts();
        /** puts an ask into the simulation based on the input */
        void makeAsk(std::string amount, std::string price, std::string product);
        /** puts an bid into the simulation based on the input */
        void makeBid(std::string amount, std::string price, std::string product);
        /** Goes to the next time frame */
        void goToNextTimeFrame();
        /** prints the exchange information to the terminal */
        void printExchange();
        /** gets the current timestamp of the simulation */
        std::string getCurrentTime();
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
        
        OrderBook orderBook{"data/big_data.csv"};
        std::string currentTime;
        Wallet wallet;
        Log log;
};
