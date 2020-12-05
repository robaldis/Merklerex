#pragma once
#include <string>
#include <map>

class Wallet{
    public:
        Wallet();
        /** insert currency into the wallet*/
        void insertCurrency(std::string type, double amount);
        /** Remove a currency from the map */
        void removeCurrency(std::string type, double amount);
        /** check if the wallet contrains an amount of a currency*/
        bool containsCurrency(std::string type, double amount);
        /** Generate a string representation of the wallet*/
        std::string toString();

    private:
        std::map<std::string, double> currency;
};
