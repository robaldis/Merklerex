#include <iostream>
#include <vector>
#include <limits>
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{
}

void MerkelMain::init() {
    int input;
    currentTime = orderBook.getEarliestTime();
    while (true) {
                printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

/** print MerkelMain::out the options the user can choose from */
void MerkelMain::printMenu() {
    // 1 print MerkelMain::help
    std::cout << "1: help" << std::endl;
    // 2 print MerkelMain::exhange stats
    std::cout << "2: exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make offer" << std::endl;
    // 4 make a bid
    std::cout << "4: Make bid" << std::endl;
    // 5 print MerkelMain::wallet
    std::cout << "5: print wallet" << std::endl;
    // 6 continue
    std::cout << "6: continue" << std::endl;
    std::cout << "==============" << std::endl;
    std::cout << "Current time: " << currentTime << std::endl;
}

void MerkelMain::printHelp() {
    std::cout << "Its simple you don't need help" << std::endl;
}
void MerkelMain::printExchange() {
    for(std::string const& p : orderBook.getKnownProducts()) {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowestPrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk() {
    std::cout << "You chose enter offer: product, price, amount, eg. ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    
    if (tokens.size() != 3) {
        std::cout << "Bad input " << input << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],tokens[2],currentTime,tokens[0],OrderBookType::ask);
            orderBook.insertOrder(obe);
        }catch(const std::exception& e) {
            std::cout << "MerkelMain::enterAsk Bad Input " << std::endl;
        }
    }

}

void MerkelMain::enterBid() {
    std::cout << "you chose enter bid" << std::endl;
}
void MerkelMain::printWallet() {
    std::cout << "youre poor" << std::endl;
}
void MerkelMain::goToNextTimeFrame() {
    std::cout << "Going to next time frame in the exchange" << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout << "There was : " << sales.size() << " number of sales" << std::endl;
    for (const OrderBookEntry& sale : sales) {
        std::cout << "Sales price: " << sale.price << "Sale amount: " << sale.amount << std::endl;
    }
    currentTime = orderBook.getNextTime(currentTime);
}

/** Use cin to get the user input to the menu */
int MerkelMain::getUserOption() {
    int userOption = 0;
    std::string stringOption;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, stringOption);
    try {
        userOption = std::stoi(stringOption);
    } catch(const std::exception& e) {
        std::cout << "Bad input" << std::endl;
    }
    std::cout << "You chose " << userOption << std::endl;
    return userOption;
}

/** take in what number the use has inputed and decide what needs to be run from that */
void MerkelMain::processUserOption(int userOption) {
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. choose 1-6" << std::endl;
    }
    if (userOption == 1) //
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printExchange();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        goToNextTimeFrame();
    }
}
