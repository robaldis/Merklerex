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
    // Write out the log vector to a csv file
    std::vector<std::string> file;
    // Open the file "log.csv" to write to
    std::ofstream out("log.csv");
    std::cout << "[SaveToFile] length of transactions: " << logData.size() << std::endl;
    for (OrderBookEntry& entry : logData) {
        std::string line = CSVReader::tokensToString(entry);

        std::cout << line << std::endl;
        out << line;
    }
    out.close();
}

/** Add an entry to the log file*/
void Log::addEntry(OrderBookEntry order) {
    logData.push_back(order);
}
