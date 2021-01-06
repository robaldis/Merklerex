#pragma once
#include <iostream>

class BotBrain {
    public:
        BotBrain();

        ProductData linearRegression(ProductData product);


    private:
        bool lr = 0.5;

};
