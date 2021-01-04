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
        /** returns vector of Orders according to the sent filters */
        std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

        /** Returns the earliest time in the order bool */
        std::string getEarliestTime();
        /** Return the next time based on the time stamp given
         *  If there is no next time stamp it will wrap around to the start */
        std::string getNextTime(std::string timestamp);
        std::string getPreviouseTime(std::string timestamp);

        void insertOrder(OrderBookEntry& obe);


        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);


        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowestPrice(std::vector<OrderBookEntry>& orders);
        static double getChange(std::vector<OrderBookEntry>& orders, std::vector<OrderBookEntry>& nextOrders);
        static double getAverage(std::vector<OrderBookEntry>& orders);
        
    private:
        std::vector<OrderBookEntry> orders;

};
