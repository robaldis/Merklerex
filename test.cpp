#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> tokenise(std::string csvLine, char separator) {


	std::string token;
	std::vector<std::string> tokens;

	signed int start, end;

	start = csvLine.find_first_not_of(separator, 0);


	do {
		end = csvLine.find_first_of(separator, start);

		if (start == csvLine.length() || start == end) {
			break;
		}
		if (end >= 0) {
			token = csvLine.substr(start,end-start);
		}
		else {
			token = csvLine.substr(start, csvLine.length() - start);
		}

		tokens.push_back(token);
		start = end +1;
	}while(end>0);

	return tokens;
}

int main() {
    // File that we want to read from
    std::ifstream csvFile{"data/book_data.csv"};
    std::string line;
    std::vector<std::string> tokens;


    if (csvFile.is_open()) {
        std::cout << "File open" << std::endl;

        while (std::getline(csvFile, line)) { // This read every line in the file
            std::cout << "Read line " << line << std::endl;
            tokens = tokenise(line, ',');
            
            if (tokens.size() != 5 ) { // Check if is bad line
                std::cout << "Bad Line" << std::endl;
                continue;
            }
            // Convert the strings into doubles
            try { 
                double price = std::stod(tokens[3]);
                double amount = std::stod(tokens[4]);
                std::cout << price << ";" << amount << std::endl;
            } catch(std::exception& e) {
                std::cout << "Could not convert string to double" << std::endl;
                continue;
            }
            
                // Print out all of the tokens for that line.
            for(const std::string& t : tokens) {
                std::cout << t << std::endl;
            }
        }

        csvFile.close();
    }
    else {
        std::cout << "Could not open file" << std::endl;
    }


}
