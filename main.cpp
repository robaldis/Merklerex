#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
// TODO: there is a weird bug when you type in "nice" it goes to infinite loop



int main() {
    MerkelMain app{};
    app.init();
    //CSVReader::readCSV("data/book_data.csv");

    return 0;
}

