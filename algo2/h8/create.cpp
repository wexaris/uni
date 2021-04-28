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

Programma izveidota: 2021/04/15
*******************************************/

#include <iostream>
#include <fstream>
#include <time.h>
#include "date.hpp"

constexpr const char* FILENAME = "dates.bin";

constexpr unsigned int DATE_COUNT = 5;
constexpr unsigned int MIN_YEAR = 2019;
constexpr unsigned int MAX_YEAR = 2020;

constexpr unsigned int YEAR_RANGE = MAX_YEAR - MIN_YEAR;
constexpr unsigned int MONTH_RANGE = 3;
constexpr unsigned int DAY_RANGE = 30;

/* Create a binary file containing a list of dates.
 * The items are not ordered.
 */
int main() {
    // Open output binary file
    std::ofstream out(FILENAME, std::ios::binary);
    if (!out) {
        std::cout << "Failed to open file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Init random number generator
    srand(time(NULL));

    // Generate and write random dates to file
    for (int i = 1; i <= DATE_COUNT; i++) {
        Date date;
        date.Year = rand() % (YEAR_RANGE + 1) + MIN_YEAR;
        date.Month = rand() % (MONTH_RANGE + 1);
        date.Day = rand() % (DAY_RANGE + 1);

        out.write((char*)&date, sizeof(Date));
    }

    return EXIT_SUCCESS;
}
