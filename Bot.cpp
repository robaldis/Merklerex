#include "Bot.h"

Bot::Bot() {

}

void Bot::init() {
    sim = MerkelMain{};
    sim.init(true);
}
