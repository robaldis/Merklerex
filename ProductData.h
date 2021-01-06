#pragma once
#include <vector>
#include <string>

class ProductData {
    public:
        ProductData(std::string name);
        std::string name;
        std::vector<double> priceOverTime;
        double m;
        double b;

};
