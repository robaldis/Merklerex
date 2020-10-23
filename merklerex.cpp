#include <iostream>
#include <string>
#include <vector>

enum class OderBookType{bid, ask};

/** Data structure to represent each row in the colum of data */
class OrderBookEntry
{
    public:
        
        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OderBookType oderType;

        OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OderBookType oderType)
        : price(price), amount(amount), timestamp(timestamp), product(product), oderType(oderType) // This is the better way to initialise parameters
        {

        }
};


/** print out the options the user can choose from */
void printMenu () 
{
    // 1 print help
    std::cout << "1: Print help" << std::endl;
    // 2 print exhange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make offer" << std::endl;

    // 4 make a bid
    std::cout << "4: Make bid" << std::endl;

    // 5 print wallet
    std::cout << "5: Print wallet" << std::endl;

    // 6 continue
    std::cout << "6: continue" << std::endl;
    std::cout << "==============" << std::endl;
}

void printHelp()
{
    std::cout << "Its simple you don't need help" << std::endl;

}
void printExchange()
{
    std::cout << "printing current exchange state" << std::endl;

}
void enterOffer()
{
    std::cout << "You chose enter offer" << std::endl;

}
void enterBid()
{
    std::cout << "you chose enter bid" << std::endl;

}
void printWallet()
{
    std::cout << "youre poor" << std::endl;

}
void goToNextTimeFrame()
{
    std::cout << "Going to next time frame in the exchange" << std::endl;

}

/** Use cin to get the user input to the menu */
int getUserOption() 
{
    int userOption;
    std::cout << "Type in 1-6" << std::endl;
    std::cin >> userOption;
    std::cout << "You chosed " << userOption << std::endl;
    return userOption;
}

/** take in what number the use has inputed and decide what needs to be run from that */
void processUserOption(int userOption) 
{
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


int main()
{

    // OrderBookEntry order1{0.0000008,49152265.030762,"2020/03/17 17:02:00.124758","DOGE/BTC",OderBookType::ask};


    std::vector<OrderBookEntry> orderBook;

    orderBook.push_back(OrderBookEntry{0.0000008,49152265.030762,"2020/03/17 17:02:00.124758","DOGE/BTC",OderBookType::ask});

    std::cout << "The price is " << orderBook[0].price << std::endl;

    while (true) 
    {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }
    return 0;
}

