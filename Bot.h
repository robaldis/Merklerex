#pragma once
#include <iostream>
#include "BotBrain.h"
#include "MerkelMain.h"


class Bot: BotBrain {
    public:
        Bot();
        void init();


    private:
        std::vector<ProductData> priceLog;
        MerkelMain sim = MerkelMain{};

};
