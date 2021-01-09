#include "Log.h"
#include "CSVReader.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>



Log::Log() {

}

/** Save the log data to a file */
void Log::saveToFile() {
    // Open the file "log.csv" to write to
    std::ofstream out("log.csv");
    std::cout << "[SaveToFile] length of transactions: " << logData.size() << std::endl;
    for (std::string& line : logData) {
        out << line;
    }
    out.close();
}

/** Add an entry to the log file*/
void Log::addEntry(OrderBookEntry order) {
    std::string line = CSVReader::tokensToString(order);
    logData.push_back(line);
}


void Log::addBalance(std::string wallet) {
    logData.push_back("-- Balance: --\n" + wallet + "--------\n");
}
