/*******************************************
Rainers Vorza, rv20039

Izveidot programmu valodā C++, kas apstrādā teksta failu secīgā režīmā.
Dati no faila jānolasa pa vienai rindiņai. Nedrīkst dublēt visa faila saturu operatīvajā atmiņā.
Sīkākas prasības sk. Laboratorijas darbu noteikumos.

F9. Izvadīt dotajā teksta failā f sastapto latīņu alfabēta burtu lietojuma
biežuma tabulu (nešķirojot lielos un mazos burtus) failā f1. Tabulai jābūt sakārtotai alfabētiski.

Programma izveidota: 2021/02/26
*******************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <map>

bool in_range(char c, char lo, char hi) { return lo <= c && c <= hi; }

int main () {
    while (true) {
        // Request input file
        std::string path;
        std::cout << "Input file (empty to exit): ";
        getline(std::cin, path); // Allows empty input, unlike `>>`

        // Exit if no input file
        if (path.empty())
            break;

        // Open input file
        std::ifstream in(path);
        if (!in.is_open()) {
            std::cerr << "Failed to open input file!" << std::endl << std::endl;
            continue;
        }

        // Use std::map to keep track of seen characters and their count
        // std::map also takes care of ordering
        std::map<char, unsigned> char_count;

        // Read file line by line, char by char
        std::string line;
        while (std::getline(in, line)) {
            for (char c : line) {
                // Uncapitalize any capitals
                if (in_range(c, 'A', 'Z'))
                    c += 32;

                // Increase character count
                if (in_range(c, 'a', 'z'))
                    char_count[c]++;
            }
        }

        // Open output file
        std::ofstream out("out.txt");
        if (!out.is_open()) {
            std::cerr << "Failed to open output file!" << std::endl << std::endl;
            continue;
        }

        // Write to output file
        for (auto c : char_count) {
            out << c.first << " " << c.second << std::endl;
            std::cout << c.first << " " << c.second << std::endl;
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}