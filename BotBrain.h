#pragma once
#include <map>
#include <vector>

class BotBrain {

    public:
        /** This will hold all the information for the brain of the bot */
        BotBrain();
        void startBrain(std::vector<std::string> products);
        void analysis(std::map<std::string, double> prices);
        void linearRegression(std::string product);
        void makePrediction(std::string prodcut);
        void addValueToData(std::string product, double averagePrice);


    private:
        // contains the name : vector of vlaues for the price over time
        std::map<std::string, std::vector<double>> data;
        std::map<std::string, std::vector<double>> regression;
        double lr = 0.2;
};
