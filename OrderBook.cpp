#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <iostream>
#include <algorithm>

OrderBook::OrderBook(std::string filename) {
    orders = CSVReader::readCSV(filename);
    
}


std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap; 
    for (OrderBookEntry& e : orders) {
        prodMap[e.product] = true;
    }
    for (auto const& e: prodMap) {
        products.push_back(e.first);
    }
    return  products;
}


std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp) {
    std::vector<OrderBookEntry> orders_sub;
    std::cout << "[getOrders] time: " << timestamp << " proudct: " << product << std::endl;
    for (OrderBookEntry& e : orders) {
        if (e.orderType == type && 
                e.product == product && 
                e.timestamp == timestamp) {
            orders_sub.push_back(e);
        }
    }
    return orders_sub; 
}


double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
    std::cout << "[getHighPrice] number of orders: " << orders.size() << std::endl;
    double max = orders[0].price;
    for (OrderBookEntry& e : orders) {
        if (e.price > max) max = e.price;
    }
    return max;
}


double OrderBook::getLowestPrice(std::vector<OrderBookEntry>& orders) {
    double min = orders[0].price;
    for (const OrderBookEntry& e : orders) {
        if (e.price < min) min = e.price;
    }
    return min;
}


/** Calculate the change from last time stamp*/
double OrderBook::getChange(std::vector<OrderBookEntry>& orders, std::vector<OrderBookEntry>& nextOrders) {
    double average1;
    double average2;
    for (OrderBookEntry& e : orders) {
        // Work out the average
        average1 += e.price;
    }
    for (OrderBookEntry& e : nextOrders) {
        // Work out the average
        average2 += e.price;
    }
    average1 = average1/orders.size();
    average2 = average2/nextOrders.size();

    return average1 - average2; 
}



std::string OrderBook::getEarliestTime() {
    return orders[0].timestamp;
}


std::string OrderBook::getNextTime(std::string timestamp) {
    std::string next_timestamp = "";
    for (const OrderBookEntry& e : orders) {
        if (e.timestamp > timestamp) {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "") {
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

std::string OrderBook::getPreviouseTime(std::string timestamp) {
    std::string previouse_timestamp = "";
    for (const OrderBookEntry& e : orders) {
        if (e.timestamp < timestamp) {
            previouse_timestamp = e.timestamp;
            break;
        }
    }
    if (previouse_timestamp == "") {
        previouse_timestamp = orders[0].timestamp;
    }
    return previouse_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry& order) {
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(),OrderBookEntry::compareByTimestamp);
}



std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
    // Get all the orders for the timestamp we are in for the product we want.
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;
    // Sort the asks and bids
    std::sort(asks.begin(),asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    // Compare each ask with every bid to find a match.
    for(OrderBookEntry& ask : asks) {
        for(OrderBookEntry& bid : bids) {
            if(bid.price >= ask.price) {
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::asksale};
                if (bid.username == "simuser") {
                    sale.orderType = OrderBookType::bidsale;
                    sale.username = "simuser";
                }
                if (ask.username == "simuser") {
                    sale.orderType = OrderBookType::asksale;
                    sale.username = "simuser";
                }
                if (bid.amount == ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;

                }
                if (bid.amount > ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;

                }
                if(bid.amount < ask.amount && bid.amount > 0){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;

                }
            }
        }
    }
    return sales;
}
