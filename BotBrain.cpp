#include "BotBrain.h"
#include <string>
#include <math.h>


BotBrain::BotBrain(){ 

}


ProductData BotBrain::linearRegression(ProductData product) {
    /**
    int m = product.m;
    int b = product.b;
    int m_gradiant = 0;
    int b_gradiant = 0;
    // NOTE: Figure out what N actually is
    int N = product.priceOverTime[0].size();
    int x = 0;
    for (const std::vector<double>& timeFrame : product.priceOverTime) {
        for (const double& y : timeFrame) {
            b_gradiant += -(2/N) * (y - ((m * x) + b));
            m_gradiant += -(2/N) * x * (y - ((m*x) + b));
            x++;
        }
    }
    product.m = m - (m_gradiant * lr);
    product.b = b - (b_gradiant * lr);

    std::cout << "[linearRegression]" << "m: " << product.m << "b: " << product.b << std::endl;

    return product;
    */

    // Least squares law
    double yAverage = 0;
    double xAverage = 0;
    int N = product.priceOverTime.size();

    if (N == 1) {
        return product;
    }


    for (int i = 0; i < N; ++i) {
        xAverage += i+1;
        yAverage+= product.priceOverTime[i];
    }
    
    yAverage = yAverage/N;
    xAverage = xAverage/N;


    double num = 0;
    double din = 0;
    for (int x=0; x < N; ++x) {
       num += (product.priceOverTime[x]-yAverage) * ((x+1)-xAverage);
       din += pow(((x+1)-yAverage), 2);   
    }

    product.m = num/din;
    product.b = yAverage-product.m*xAverage;
    
    std::cout << "m: " << product.m << " b: " << product.b << std::endl;
    return product;

}



std::vector<std::string> BotBrain::prediction(ProductData product) {
    std::vector<std::string> sale;
    std::cout << "[prediction] the if thing: " <<  (product.m > variance)<< std::endl;
    if (product.m > variance || product.m < -variance) {
        // is it a big enough gradient to be worth it?
        // The next two if statements define if it will be a bid or ask
        if (product.m < 0) {
            // The market is going up for this product
            sale.push_back("bid");
        }
        if (product.m > 0) {
            // The market is going down for this product
            sale.push_back("ask");
        } 
    } else {
        // there is not a big enough change in the market.
        sale.push_back("none");
        return sale;
    }
    double salePrice = product.m*product.priceOverTime.size() + product.b;

    std::cout << "salePrice: " << salePrice << std::endl;
    std::cout << "[prediction] m: " << product.m << " b: " << product.b << std::endl;
    std::cout << "[prediction] Sale price: " <<  std::floor((salePrice * 100) + .5) / 100 << " Current average price: " << product.priceOverTime[product.priceOverTime.size()-1] << std::endl;

     
    sale.push_back("1.0");
    // std::to_string() has a precision of 6 d.p
    sale.push_back(std::to_string(salePrice));
    std::cout << "The product name is: " << product.name << std::endl;
    sale.push_back(product.name);

    std::cout << "another moment of the sale price: " << sale[2] << std::endl;
    std::cout << "sale price to string: " << std::to_string(salePrice) << std::endl;
    return sale;
}
