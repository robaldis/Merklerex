#include "Bot.h"
#include <iostream>

Bot::Bot() {

}

void Bot::init() {
    sim = MerkelMain{};
    sim.init(true);
    while(true) {
        // This is the "think" loop
        // takes in: product, avarege price.
        //sim.getAllAveragePrice();
        //analysis();
        // do analysis()
        // execute tasks
    }
}


void Bot::makeBid(std::string amount, std::string price, std::string product) {
    sim.makeBid(amount, price, product);
}

void Bot::makeAsk(std::string amount, std::string price, std::string product) {
    // would need to convert double to stirng. maybe do that here maybe
    // probably done in another function
    sim.makeAsk(price, amount, product);
}
