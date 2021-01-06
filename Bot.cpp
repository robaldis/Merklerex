#include "Bot.h"
#include <iostream>

Bot::Bot() {

}

void Bot::init() {
    sim = MerkelMain{};
    sim.init(true);
    startBrain(sim.getKnownProducts());

    analysis(sim.getAllAveragePrice());
    sim.goToNextTimeFrame();
    analysis(sim.getAllAveragePrice());
    while(true) {
        // This is the "think" loop
        // takes in: product, avarege price.
        //  analysis(sim.getAllAveragePrice());
        // do analysis()
        // sim.goToNextTimeFrame();
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
