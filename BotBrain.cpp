#include "BotBrain.h"


BotBrain::BotBrain(){
}



// prediction for next time step
void BotBrain::analysis(std::map<std::string, double> prices) {
    for (const std::pair<std::string, double>& row : prices) {
        addValueToData(row.first, row.second);
        linearRegression(row.first);
    }
}

void BotBrain::linearRegression(std::string product) {
    int m = regression[product][0];
    int b = regression[product][1];
    int m_gradiant = 0;
    int b_gradiant = 0;
    int N = data[product].size();
    int x = 0;
    for (const double y : data[product]) {
        b_gradiant += -(2/N) * (y - ((m * x) + b));
        m_gradiant += -(2/N) * x * (y - ((m*x) + b));

        x++;
    }
    regression[product][0]= m - (m_gradiant * lr);
    regression[product][1] = b - (b_gradiant * lr);
}


void BotBrain::makePrediction(std::string product) {
    double m = regression[product][0];
    double b = regression[product][1];
    int x = data.size();
    // prediction for next time step
    double y = m*x+b; 


    if (m > 0) {
        // The market is going up Bye now

    }
    else if (m < 0) {
        // The market is going down Sell now

    }

}

void BotBrain::addValueToData(std::string product, double averagePrice) {
    data[product].push_back(averagePrice);
}
