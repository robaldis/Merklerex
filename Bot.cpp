#include "Bot.h"

Bot::Bot() {

}

void Bot::init() {
    sim = MerkelMain{};
    sim.init(true);
}


void Bot::makeBid(double amount, double price, std::string product) {
    sim.makeBid(amount, price, product);
}

void Bot::makeAsk(double amount, double price, std::string product) {
    // would need to convert double to stirng. maybe do that here maybe
    // probably done in another function
    sim.makeAsk(price, amount, product);
}
