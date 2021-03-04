#include <iostream>

int main() {
    unsigned n;
    std::cout << "N: ";
    std::cin >> n;

    // Atkārto piecas reizes, palielinot m
    int count = 0;
    for (unsigned i = n; count < 5; i++) {
        // Atrod pirmo ciparu
        unsigned first = i;
        while (first >= 10) first /= 10;
        // Atrod pēdējo ciparu
        unsigned last = i % 10;

        if ((first + last) % 2 == 1) {
            std::cout << i << std::endl;
            count++;
        }
    }
}