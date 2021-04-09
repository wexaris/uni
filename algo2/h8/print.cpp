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
#include "date.hpp"

int main() {
    // Open input binary file
    std::ifstream in("dates.bin", std::ios::binary);
    if (!in) {
        std::cout << "Failed to open file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Get file length
    in.seekg(0, in.end);
    size_t len = in.tellg();
    in.seekg(0, in.beg);

    // Print dates from file
    while (in.tellg() < len) {
        Date date;
        in.read((char*)&date, sizeof(Date));
        std::cout << date.to_string() << std::endl;
    }

    return EXIT_SUCCESS;
}
