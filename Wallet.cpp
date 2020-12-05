#include "Wallet.h"
#include <iostream>
#include <vector>
#include "CSVReader.h"


Wallet::Wallet() {

}

/** insert currency into the wallet*/
void Wallet::insertCurrency(std::string type, double amount) {
    int balance;
    if (amount < 0 ) {
        throw std::exception();
    }
    if (currency.count(type) == 0) {// not there yet {
        balance = 0;
    }
    else {
        balance = currency[type];

    }
    balance += amount; 
    currency[type] = balance;

}

bool Wallet::removeCurrency(std::string type, double amount) {
    if (amount < 0 ) {
        return false;
    }
    if (currency.count(type) == 0) {// not there yet {
        return false;
    }
    else {
        if (containsCurrency(type, amount)) {
            currency[type] -= amount;
            return true;
        }
    }
    return false;
}
        
        
/** check if the wallet contrains an amount of a currency*/
bool Wallet::containsCurrency(std::string type, double amount) {
    if (currency.count(type) == 0)
        return false;
    else
        return currency[type] >= amount;

}



std::string Wallet::toString() {
    if (currency.empty()) {
        return "Nothing in the wallet";
    }
    std::string output;
    for (const std::pair<std::string, double>& row : currency) {
        output += row.first + " : " + std::to_string(row.second) + "\n";
    }
    return output;
}


bool Wallet::canFulfillOrder(OrderBookEntry order) {
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    // ask
    if (order.orderType == OrderBookType::ask) {
        double amount = order.amount;
        std::string curr = currs[0];
        return containsCurrency(curr, amount);
    }
    // bid
    if (order.orderType == OrderBookType::bid) {
        double amount = order.amount * order.price;
        std::string curr = currs[1];

        return containsCurrency(curr, amount);
    }
    return false;
}
