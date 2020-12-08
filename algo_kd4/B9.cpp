#include <iostream>
#include <string>

unsigned count(const std::string& str, char x) {
    unsigned i = 0;
    for (const char& c : str)
        if (c == x)
            i++;
    return i;
}

int main() {
    std::string str;
    std::cout << "Teksts: ";
    std::getline(std::cin, str);
    std::cin.clear();

    char x;
    std::cout << "Simbols: ";
    std::cin.get(x);

    std::cout << "Simbola skaits: " << count(str, x) << std::endl;
}
