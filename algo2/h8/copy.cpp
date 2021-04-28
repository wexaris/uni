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
#include <list>
#include "date.hpp"

constexpr const char* FILENAME = "dates.bin";
constexpr const char* ASCENDING_OUT = "ascending.txt";
constexpr const char* DESCENDING_OUT = "descending.txt";

// Date comparison function
// Ensures ascending order when used for sorting
bool date_compare(const Date& a, const Date& b) {
    if (a.Year == b.Year) {
        if (a.Month == b.Month) {
            return a.Day < b.Day;
        }
        return a.Month < b.Month;
    }
    return a.Year < b.Year;
}

/* Create two readable copies of a dates.bin file.
 * One copy is in ascending order.
 * One copy is in descending order.
 */
int main() {
    // Open input binary file
    std::ifstream in(FILENAME, std::ios::binary);
    if (!in) {
        std::cout << "Failed to open file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Get file length
    in.seekg(0, in.end);
    size_t len = in.tellg();
    in.seekg(0, in.beg);

    // Collect dates from file
    std::list<Date> dates;
    while (in.tellg() < len) {
        Date date;
        in.read((char*)&date, sizeof(Date));
        dates.push_back(std::move(date));
    }
    in.close();

    // Sort dates in ascending order
    dates.sort(date_compare);

    { // Write dates in ascending order
        std::ofstream out_asc(ASCENDING_OUT);
        if (!out_asc) {
            std::cout << "Failed to open file!" << std::endl;
        }

        for (auto iter = dates.begin(); iter != dates.end(); iter++) {
            std::string date_str = iter->to_string() + "\n";
            out_asc.write(date_str.c_str(), date_str.size());
        }
    }

    { // Write dates in descending order
        std::ofstream out_desc(DESCENDING_OUT);
        if (!out_desc) {
            std::cout << "Failed to open file!" << std::endl;
        }

        for (auto iter = dates.rbegin(); iter != dates.rend(); iter++) {
            std::string date_str = iter->to_string() + "\n";
            out_desc.write(date_str.c_str(), date_str.size());
        }
    }

    return EXIT_SUCCESS;
}
