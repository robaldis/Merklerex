#include <vector>
#include <string>
#include "Bot.h"
#include "OrderBookEntry.h"
#include "OrderBook.h"

Bot::Bot() {}

void Bot::init() {
    std::cout << "The Bot has been created and is not controlling the simulation" << std::endl;
    sim.init(true);
    std::vector<std::string> products = sim.getKnownProducts();
    initPriceLog(products);

    std::map<std::string, std::vector<OrderBookEntry>> orders = sim.getExchangeData();
    formatExchangeData(orders);
    // printOrders(orders);
    // sim.goToNextTimeFrame();
    // printOrders(orders);
}

void Bot::formatExchangeData(std::map<std::string, std::vector<OrderBookEntry>> orders) {
    // Loop through all the products
    // collecte the average price for that product
    // put that inside the priceLog var
    

    for (auto& product : orders) {
        std::string p = product.first;
        std::vector<OrderBookEntry> o = product.second;
        double average = 0;
        for (OrderBookEntry orderEntry : o) {
            average += orderEntry.price;
        }
        average = average / o.size();
        std::cout << "[FormatExchangeData] average: " << average << std::endl;

        // place into our new array
        for (ProductData log : priceLog) {
            if (log.name == p) {
                log.priceOverTime.push_back(average);
            }
        }
    }

    //BREAK: Make sure the data is going in corectly


}


void Bot::initPriceLog(std::vector<std::string> products) {
    for (std::string product : products) {
        priceLog.push_back(ProductData{product});
    }
}


void Bot::printOrders(std::vector<OrderBookEntry> orders, std::string product) {
    for (auto& order : orders) {
        std::cout << "Order Price: " << order.price << " Product: " << product << std::endl;
    }
}

void Bot::printPriceLog() {
    for (ProductData& prod : priceLog) {
        std::cout << "Name: " << prod.name << std::endl;
    }
}
