#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
// TODO: there is a weird bug when you type in "nice" it goes to infinite loop



int main() {
    MerkelMain app{};
    app.init();
    // // OrderBookEntry order1{0.0000008,49152265.030762,"2020/03/17 17:02:00.124758","DOGE/BTC",OderBookType::ask};

    // std::vector<OrderBookEntry> orderBook;

    // orderBook.push_back(OrderBookEntry{0.0000008,49152265.030762,"2020/03/17 17:02:00.124758","DOGE/BTC",OrderBookType::ask});

    // std::cout << "The price is " << orderBook[0].price << std::endl;

    // while (true) 
    // {
    //     printMenu();
    //     int userOption = getUserOption();
    //     processUserOption(userOption);
    // }
    return 0;
}

