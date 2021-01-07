#include "BotBrain.h"
#include <string>


BotBrain::BotBrain(){ 

}


ProductData BotBrain::linearRegression(ProductData product) {
    int m = product.m;
    int b = product.b;
    int m_gradiant = 0;
    int b_gradiant = 0;
    int N = product.priceOverTime.size();
    int x = 0;
    for (const double& y : product.priceOverTime) {
        b_gradiant += -(2/N) * (y - ((m * x) + b));
        m_gradiant += -(2/N) * x * (y - ((m*x) + b));
        x++;
    }
    product.m = m - (m_gradiant * lr);
    product.b = b - (b_gradiant * lr);

    std::cout << "[linearRegression]" << "m: " << product.m << "b: " << product.b << std::endl;

    return product;
}


std::vector<std::string> BotBrain::prediction(ProductData product) {
    std::vector<std::string> sale;
    if (product.m > variance && product.m < -variance) {
        // is it a big enough gradient to be worth it?
        // The next two if statements define if it will be a bid or ask
        if (product.m > 0) {
            // The market is going up for this product
            sale.push_back("bid");
        }
        if (product.m < 0) {
            // The market is going down for this product
            sale.push_back("ask");
        } 
    } else {
        // there is not a big enough change in the market.
        sale.push_back("none");
        return sale;
    }
    double salePrice = product.m*product.priceOverTime.size() + product.b;

    std::cout << "[prediction] m: " << product.m << std::endl;
    std::cout << "[prediction] Sale price: " << salePrice << " Current average price: " << product.priceOverTime[product.priceOverTime.size()-1] << std::endl;

     
    sale.push_back("1.0");
    sale.push_back(std::to_string(salePrice));
    std::cout << "The product name is: " << product.name << std::endl;
    sale.push_back(product.name);

    return sale;
}
