#pragma once 
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"


class OrderBook {
    public:
        /** construct, reading a csv data file */
        OrderBook(std::string filename);
        /** return vector of all known products in the dataset */
        std::vector<std::string> getKnownProducts();
        /** returrns vector of Orders according to the sent filters */
        std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

        /** Returns the earliest time in the order bool */
        std::string getEarliestTime();
        /** Return the next time based on the time stamp given
         *  If there is no next time stamp it will wrap around to the start */
        std::string getNextTime(std::string timestamp);
        /** gets the previosue timestamp of the simulation */
        std::string getPreviouseTime(std::string timestamp);

        /** insert OrderBookEntry into the OrderBook */
        void insertOrder(OrderBookEntry& obe);


        /** Matching engine that matches all the asks to bids */
        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        /** get the high price of a vector of orders */
        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        /** get the low price of a vector of orders */
        static double getLowestPrice(std::vector<OrderBookEntry>& orders);
        /** get the change of price of a vector of orders */
        static double getChange(std::vector<OrderBookEntry>& orders, std::vector<OrderBookEntry>& nextOrders);
        
    private:
        std::vector<OrderBookEntry> orders;

};
