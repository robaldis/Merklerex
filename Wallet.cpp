#include "Wallet.h"
#include <iostream>

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

void Wallet::removeCurrency(std::string type, double amount) {
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
    balance -= amount; 
    currency[type] = balance;
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
