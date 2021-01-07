#pragma once
#include <iostream>
#include "ProductData.h"

class BotBrain {
    public:
        BotBrain();

        ProductData linearRegression(ProductData product);
        std::vector<std::string> prediction(ProductData proudct);


    private:
        double lr = 0.5;
        double variance = 0.2;

};
