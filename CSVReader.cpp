#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader() {

}

//** */ 
std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName) {
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFileName};
    std::string line;

    if (csvFile.is_open()) {
        while(std::getline(csvFile, line)) {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line,',')); 
                entries.push_back(obe);
            } catch(const std::exception& e) {
                std::cout << "CSVReader::readCSV bad data" << std::endl;
            }
        }
    }
    std::cout << "CSVReader::readCSV read: " << entries.size() << std::endl;
    return entries;
}

/** Takes in a csv string and seperator and seperates out the string returns a vector */
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator) {
	std::string token;
	std::vector<std::string> tokens;

	signed int start, end;

	start = csvLine.find_first_not_of(separator, 0);

	do {
		end = csvLine.find_first_of(separator, start);

		if (start == csvLine.length() || start == end) {
			break;
		}
		if (end >= 0) {
			token = csvLine.substr(start,end-start);
		}
		else {
			token = csvLine.substr(start, csvLine.length() - start);
		}

		tokens.push_back(token);
		start = end +1;
	}while(end>0);

	return tokens;
}


OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {

    double price;
    double amount;
    
    if (tokens.size() != 5 ) { // Check if is bad line
        std::cout << "Bad Line" << std::endl;
        throw std::exception();
    }
    // Convert the strings into doubles
    try { 
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    } catch(const std::exception& e) {
        std::cout << "Could not convert string to double" << std::endl;
        throw;
    }



    OrderBookEntry obe{price,
        amount,
        tokens[0],
        tokens[1],
        OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}
 
OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
        std::string amountString,
        std::string timestamp,
        std::string product,
        OrderBookType orderType){ 


    double price;
    double amount;
    
    // Convert the strings into doubles
    try { 
        price = std::stod(priceString);
        amount = std::stod(amountString);
    } catch(const std::exception& e) {
        std::cout << "CSVReader::stringToOBE Bad float!" << priceString << std::endl;
        std::cout << "CSVReader::stringToOBE Bad float!" << amountString << std::endl;
        throw;
    }



    OrderBookEntry obe{price,
        amount,
        timestamp,
        product,
        orderType};
    return obe;
}




std::string CSVReader::tokensToString(OrderBookEntry order) {
    std::string line;
    line += order.timestamp;
    line += "," + order.product;
    line += "," + std::to_string(order.price);
    line += "," + std::to_string(order.amount) + "\n";
    return line;

}

