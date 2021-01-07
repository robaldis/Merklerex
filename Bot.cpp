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
    // init the price log with all the products being used.
    initPriceLog(products);

    std::map<std::string, std::vector<OrderBookEntry>> orders = sim.getExchangeData();
    formatExchangeData(orders);
    for (ProductData& product : priceLog) {
        sim.printExchange();
        product = linearRegression(product);
        std::vector<std::string> sale = prediction(product);
        processSale(sale);
        sim.printExchange();
    }

    sim.goToNextTimeFrame();


    orders = sim.getExchangeData();
    formatExchangeData(orders);
    for (ProductData& product : priceLog) {
        sim.printExchange();
        product = linearRegression(product);
        std::vector<std::string> sale = prediction(product);
        processSale(sale);
        sim.printExchange();
    }
    // printOrders(orders);
    // sim.goToNextTimeFrame();
    // printOrders(orders);
}


void Bot::run() {
    /** Runs the bots traiding */
    while (true) {
        // Collect the exchange data
        std::map<std::string, std::vector<OrderBookEntry>> orders = sim.getExchangeData();
        // Format that data 
        formatExchangeData(orders);
        for (ProductData& product : priceLog) {
            // Run the linear regression
            product = linearRegression(product);
            // make prediction
            
            // Action

        }
        // go to next time frame
        sim.goToNextTimeFrame();
    }

}


void Bot::processSale(std::vector<std::string>& s){
    std::cout << "[ProcessSale] type: " << s[0] << std::endl;
    if (s[0] != "none") {
        std::string product = s[3];
        std::string amount = s[1];
        std::string price = s[2];
        std::cout << "type: " << s[0] << std::endl;

        if(s[0] == "bid") {
            std::cout << "[processSale] Making Bid" << std::endl;
            sim.makeBid(amount,price,product);

        } else if (s[0] == "ask") {
            std::cout << "[processSale] Making Ask" << std::endl;
            sim.makeAsk(amount,price,product);
        }
    }
}

void Bot::formatExchangeData(std::map<std::string, std::vector<OrderBookEntry>> orders) {
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
        for (ProductData& log : priceLog) {
            if (log.name == p) {
                log.priceOverTime.push_back(average);
            }
        }
    }

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
        std::cout << "Average price over time: ";
        for (double& average : prod.priceOverTime) {
            std::cout << average << ", ";
        }
        std::cout << std::endl;
    }
}
