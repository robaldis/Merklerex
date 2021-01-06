#include <iostream>
#include <vector>
#include <limits>
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{
}

void MerkelMain::init(bool bot) {
    int input;
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10.0);
    wallet.insertCurrency("BTC", 1000);
    if (bot) {
        std::cout << "The simulation is being controlled by a bot" << std::endl;
    }
    else {
        while (true) {
            printMenu();
            input = getUserOption();
            processUserOption(input);
        }
    }
}


void MerkelMain::makeBid(std::string amount, std::string price, std::string product) {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(price,amount,currentTime,product,OrderBookType::bid);
            obe.username="simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "not enough money. " << std::endl;
            }
        }catch(const std::exception& e) {
            std::cout << "MerkelMain::enterAsk Bad Input " << std::endl;
        }
}
void MerkelMain::makeAsk(std::string amount, std::string price, std::string product) {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(price,amount,currentTime,product,OrderBookType::ask);
            obe.username="simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "not enough money. " << std::endl;
            }
        }catch(const std::exception& e) {
            std::cout << "MerkelMain::enterAsk Bad Input " << std::endl;
        }
}


std::map<std::string,double> MerkelMain::getAllAveragePrice() {
    // for each product
    std::map<std::string, double> allAveragePrices;
    for(std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> O = orderBook.getOrders(OrderBookType::ask,
                p, currentTime);
        std::vector<OrderBookEntry> O2 = orderBook.getOrders(OrderBookType::bid,
                p, currentTime);

        O.insert(O.end(), O2.begin(), O2.end());

        allAveragePrices[p] = OrderBook::getAverage(O);
    }
    return allAveragePrices;
}


std::vector<std::string> MerkelMain::getKnownProducts() {
    return orderBook.getKnownProducts();
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
        
        std::vector<OrderBookEntry> nextEntries = orderBook.getOrders(OrderBookType::ask,
                p, orderBook.getPreviouseTime(currentTime));

        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowestPrice(entries) << std::endl;
        std::cout << "Voulme: " << OrderBook::getChange(entries,nextEntries) << std::endl;
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
        makeAsk(tokens[1],tokens[2], tokens[0]);
    }

}

void MerkelMain::enterBid() {
    std::cout << "you chose enter bid" << std::endl;
    // input a bid: type1, type 2, amount1, amount2
    std::cout << "You chose enter offer: product, price, amount, eg. ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    
    if (tokens.size() != 3) {
        std::cout << "Bad input " << input << std::endl;
    } else {
        makeBid(tokens[1],tokens[2],tokens[0]);
    }

}
void MerkelMain::printWallet() {
    std::cout << "youre poor" << std::endl;
    std::cout << wallet.toString() << std::endl;
}
void MerkelMain::goToNextTimeFrame() {
    std::cout << "Going to next time frame in the exchange" << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout << "There was : " << sales.size() << " number of sales" << std::endl;
    for (OrderBookEntry& sale : sales) {
        std::cout << "Sales price: " << sale.price << "Sale amount: " << sale.amount <<"\t" << sale.username << std::endl;
        if (sale.username == "simuser") {
            wallet.processSale(sale);
        }
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
