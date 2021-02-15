#pragma once
#include "OrderBookEntry.h"
#include <vector>

// TODO: setup a function that will create a log and save it at the end of the 
// simulation

class Log {
    public:
        Log();

        /** Save the log data to a file */
        void saveToFile();
        /** Add an entry to the log file*/
        void addEntry(OrderBookEntry order);
        /** Adds the balance to the log file */
        void addBalance(std::string wallet);

    private:
        std::vector<std::string> logData;
        

};
