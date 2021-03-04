// 2. Uzdevums (I) - ierinda
// Fizkultūras stundā zēniem ir jānosauc augums centimetros un
// jānostājas ierindā pēc auguma. Jāuzraksta programma, kas prasa ievadīt
// augumu 20 zēniem. Pēc katra ievades izdrukā ierindu, kādā secībā zēni
// nostājušies. Izdrukāt attiecīgos augumus centimetros.
//
// Rainers Vorza
// rv20039

#include <iostream>

int main() {
    int boys[20];

    // Savacam datus par katru no 20 zeniem
    for (int i = 0; i < 20; i++) {
        unsigned in;
        std::cout << "Ievadi " << i + 1 << ". zena augumu: ";
        std::cin >> in;

        // Nosakam ievadita skaitla pareizo poziciju
        int j = 0;
        for (; j < i; j++) {
            if (in < boys[j])
                break;
        }

        // Parvietojam elemntus [j, i) vienu poziciju talak
        for (int k = i - 1; k >= j; k--) {
            boys[k + 1] = boys[k];
        }

        // Ievietojam jauno vertibu sava vieta
        boys[j] = in;

        // Izprintejam pasreizejo ierindu
        std::cout << "Ierinda ";
        for (int l = 0; l <= i; l++)
            std::cout << boys[l] << " ";
        std::cout << std::endl;
    }
}