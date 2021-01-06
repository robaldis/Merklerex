#include "BotBrain.h"


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

    std::cout << "[linearRegression]" << "m: " << b_gradiant << "b: " << regression[product][1] << std::endl;

    return product;
}
