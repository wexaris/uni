/*******************************************
Rainers Vorza, rv20039

Izveidot programmu valodā C++. Ja programma darbojas ar failu, nedrīkst
dublēt visa faila saturu operatīvajā atmiņā.
Ar faila komponenti tiek saprasts fiksēta garuma ieraksts.
Sīkākās prasības sk. Laboratorijas darbu noteikumos.

H8. Dots binārs fails, kura glabājas datumi, un kura ieraksta struktūra ir
sekojoša: gads (int), mēnesis (int), diena (int). Izdrukāt informāciju divos
citos teksta failos, kur tie sakārtoti attiecīgi hronoloģiski dilstoši vai
augoši. Informācijas ielasīšanai un sakārtošanas nodrošināšanai izmantot
struktūru STL map vai STL list. Papildus izveidot palīgprogrammas binārā faila
izveidošanai un tā satura izdrukāšanai.

Programma izveidota: 2021/04/09
*******************************************/

#include <iostream>
#include <fstream>
#include <time.h>
#include "date.hpp"

constexpr unsigned int DATE_COUNT = 20;
constexpr unsigned int MIN_YEAR = 2000;
constexpr unsigned int MAX_YEAR = 2021;

constexpr unsigned int YEAR_RANGE = MAX_YEAR - MIN_YEAR;
constexpr unsigned int MONTH_RANGE = 12;
constexpr unsigned int DAY_RANGE = 30;

int main() {
    // Open output binary file
    std::ofstream out("dates.bin", std::ios::binary);
    if (!out) {
        std::cout << "Failed to open file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Init random for date generation
    srand(time(NULL));

    // Generate and write dates to file
    for (int i = 1; i <= DATE_COUNT; i++) {
        Date date;
        date.Year = rand() % (YEAR_RANGE + 1) + MIN_YEAR;
        date.Month = rand() % (MONTH_RANGE + 1);
        date.Day = rand() % (DAY_RANGE + 1);

        out.write((char*)&date, sizeof(Date));
    }

    return EXIT_SUCCESS;
}
