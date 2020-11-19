#include <iostream>
#include <vector>
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
                p,
                "2020/03/17 17:01:24.884492");
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getLowestPrice(entries) << std::endl;
    }
}

void MerkelMain::enterOffer() {
    std::cout << "You chose enter offer" << std::endl;
}
void MerkelMain::enterBid() {
    std::cout << "you chose enter bid" << std::endl;
}
void MerkelMain::printWallet() {
    std::cout << "youre poor" << std::endl;
}
void MerkelMain::goToNextTimeFrame() {
    std::cout << "Going to next time frame in the exchange." << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}

/** Use cin to get the user input to the menu */
int MerkelMain::getUserOption() {
    int userOption;
    std::cout << "Type in 1-6" << std::endl;
    std::cin >> userOption;
    std::cout << "You chose" << userOption << std::endl;
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
        enterOffer();
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
