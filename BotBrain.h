#pragma once
#include <iostream>
#include "ProductData.h"

class BotBrain {
    public:
        BotBrain();

        /** Implementing linear regresion which is how the bots will decide whi
         * way the merket is going */
        ProductData linearRegression(ProductData product);
        /** Predicts if the market is going up or down and making generating 
         * information for bid or ask */
        std::vector<std::string> prediction(ProductData proudct);


    private:
        double variance = 0.00000005;

};
