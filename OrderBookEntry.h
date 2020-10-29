#pragma once // Standard thing to only inlcude it more than one times
#include <string>


enum class OrderBookType{bid, ask};

/** Data structure to represent each row in the colum of data */
class OrderBookEntry {
	public:
		OrderBookEntry(double price,
			double amount,
			std::string timestamp,
			std::string product,
			OrderBookType orderType);	
			
		double price;
		double amount;
		std::string timestamp;
		std::string product;
		OrderBookType orderType;
		
			
		
};
