#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"
// TODO: there is a weird bug when you type in "nice" it goes to infinite loop



int main() {
    MerkelMain app{};
    app.init();
    //CSVReader::readCSV("data/book_data.csv");
    /**
    Wallet wallet;
    wallet.insertCurrency("BTC", 10);
    wallet.insertCurrency("USD", 1000);
    std::cout << wallet.toString() << std::endl;
    std::cout << "Wallet has BTC: " << wallet.containsCurrency("BTC", 0) << std::endl;
    wallet.removeCurrency("BTC", 5);
    std::cout << "Wallet has BTC: " << wallet.containsCurrency("BTC", 0) << std::endl;
    std::cout << wallet.toString() << std::endl;
*/
    return 0;
}

