#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader {

    public:
        CSVReader();
        /** Reads a csv file with the input file name */
        static std::vector<OrderBookEntry> readCSV(std::string csvFile);
        /** converts a string to vector of strings where there is the seperator
         * character */
        static std::vector<std::string> tokenise(std::string csvLine, char separator);
        /** Converts strings to an OrderBookEntry */
        static OrderBookEntry stringsToOBE(std::string priceString,
                std::string amountString,
                std::string timestamp,
                std::string product,
                OrderBookType orderType);


        /** convert a obe to a string */
        static std::string tokensToString(OrderBookEntry order);

    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
    
};
