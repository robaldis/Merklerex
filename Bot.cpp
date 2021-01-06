#include <vector>
#include <string>
#include "Bot.h"
#include "OrderBookEntry.h"

Bot::Bot() {}

void Bot::init() {
    std::cout << "The Bot has been created and is not controlling the simulation" << std::endl;
    sim.init(true);

    std::vector<OrderBookEntry> orders = sim.getExchangeData();
    printOrders(orders);
    sim.goToNextTimeFrame();
    printOrders(orders);
}


void Bot::printOrders(std::vector<OrderBookEntry> orders) {
    for (auto& order : orders) {
        std::cout << "Order Price: " << order.price << std::endl;
    }
}
