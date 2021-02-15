#include <vector>
#include <string>
#include <math.h>
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
    startTime = sim.getCurrentTime();
}


void Bot::run() {
    /** Runs the bots traiding */
    while (runBot) {
        // Collect the exchange data
        std::map<std::string, std::vector<OrderBookEntry>> orders = sim.getExchangeData();
        std::cout << "[run] length of orders: " << orders.size() << std::endl;
        // Format that data 
        formatExchangeData(orders);
        for (ProductData& product : priceLog) {
            // Run the linear regression
            product = linearRegression(product);
            // make prediction
            product = linearRegression(product);
            std::vector<std::string> sale = prediction(product);
            // sim.printExchange();
            // Action
            processSale(sale);
        }
        // go to next time frame
        sim.goToNextTimeFrame();
        if (startTime == sim.getCurrentTime()) {
            runBot = false;
        }
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

void Bot::formatExchangeData(std::map<std::string, std::vector<OrderBookEntry>>& orders) {
    for (const std::pair<std::string, std::vector<OrderBookEntry>>& product : orders) {
        std::string p = product.first;
        std::vector<OrderBookEntry> o = product.second;
        if ( o.size() == 0) {
            // Do nothing
            break;
        }
        double average = 0;
        std::vector<double> priceData;
        for (OrderBookEntry orderEntry : o) {
            if (std::isnan(orderEntry.price)) {
                std::cout << orderEntry.price << std::endl; 
            } else {
                average += orderEntry.price;
                //priceData.push_back(orderEntry.price);
            }
        }
        average = average / o.size();

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
            // std::cout << average << ", ";
        }
        std::cout << std::endl;
    }
}
