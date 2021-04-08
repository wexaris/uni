#include <iostream>
#include <fstream>
#include <vector>

bool is_numeric(char c) {
    return '0' <= c && c <= '9';
}

void longestDigitSequencePlus(const std::string& path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cerr << "Failed to open path!" << std::endl;
        return;
    }

    // Collect numeric strings
    char c;
    std::vector<std::string> values; // int may overflow
    std::string curr;
    while (fin >> c) {
        std::cout << "Check " << c << std::endl;
        if (is_numeric((c))) {
            curr += c;
        }
        else {
            std::cout << "Nonnumeric" << std::endl;
            if (!curr.empty()) {
                std::cout << "Store " << curr << std::endl;
                values.push_back(curr);
                curr.clear();
            }
        }
    }
    if (!curr.empty()) {
        std::cout << "Store " << curr << std::endl;
        values.push_back(curr);
        curr.clear();
    }

    // Find longest or largest numeric string
    std::string longest;
    for (unsigned i = 0; i < values.size(); i++) {
        // Compare length
        if (longest.length() < values[i].length()) {
            longest = values[i];
        }
        // Compare chars, save string with largest
        else if (longest.length() == values[i].length()) {
            for (unsigned j = 0; j < values.size(); j++) {
                if (longest[j] < values[i][j]) {
                    longest = values[i];
                    break;
                }
            }
        }
    }

    if (!longest.empty())
        std::cout << "Garaka skaitlu virkne: " << longest << std::endl;
    else
        std::cout << "Nav nevienas skaitlu virkes!" << std::endl;
}


int main() {

    longestDigitSequencePlus("input.txt");

    return 0;
}