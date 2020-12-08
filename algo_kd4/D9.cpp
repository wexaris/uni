#include <iostream>
#include <cstring>

char* shorten(char* str) {
    size_t len = strlen(str);
    size_t newlen = (len / 2) + len % 2;
    char* newStr = new char[newlen + 1];
    for (size_t i = 0, j = 0; i < len; i++)
        if (i % 2 == 0)
            newStr[j++] = str[i];
    return newStr;
}

int main() {
    char str[1024];
    std::cout << "Teksts: ";
    std::cin.getline(str, 1023);

    char* newStr = shorten(str);
    std::cout << "Saisinats: " << newStr << std::endl;
    delete[] newStr;
}
