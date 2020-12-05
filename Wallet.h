#pragma once
#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet{
    public:
        Wallet();
        /** insert currency into the wallet*/
        void insertCurrency(std::string type, double amount);
        /** Remove a currency from the map */
        bool removeCurrency(std::string type, double amount);
        /** check if the wallet contrains an amount of a currency*/
        bool containsCurrency(std::string type, double amount);
        /** Generate a string representation of the wallet*/
        std::string toString();
        /** Checks if the wallet has the funds to complete a bid*/
        bool canFulfillOrder(OrderBookEntry order);

    private:
        std::map<std::string, double> currency;
};
