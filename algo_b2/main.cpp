/*******************************************
Rainers Vorza, rv20039
B2. Dots naturāls skaitlis n < 1000. Izdrukāt doto skaitli romiešu pierakstā.
Programma izveidota: 05/10/2020
*******************************************/

// Rezultātu tabula:
//    n   |   CPPRezultāts   |   PyRezultāts    |    Paredzēts     | Sakrīt
// -------|------------------|------------------|------------------|--------
//    420 |             CDXX |             CDXX |             CDXX |   X
//   1000 |                M |                M |                M |   X
//      0 | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
//     -1 | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
//    txt | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X

#include <iostream>
#include <string>

// Romiešu cipars - tā simbols un vērtība
struct RomanNumeral {
    std::string Symbol;
    int Value;
};

int main() {
    std::string inputStr; // Ievadītais teksts
    int inputNum;         // Naturalais skaitlis (uzd. 'n')

    std::cout << "Ievadiet ENTER lai beigtu\n";

    while (true) {
        // Saņemam naturālo skaitli no lietotāja.
        // Izmantojam getline(), jo >> neļauj ievadīt tukšu rindu.
        // Ja ir tukšums, apturam programmu.
        std::cout << "Ievadiet naturalu skaitli: ";
        getline(std::cin, inputStr);
        if (inputStr.empty())
            break;

        try {
            inputNum = stoi(inputStr); // Pārplūdes gadījumā met izņēmumu
            // Pārliecinamies, ka ievadītais skaitlis ir 1 - 1000
            if (0 >= inputNum || inputNum > 1000)
                throw std::runtime_error("skaitlim jabut 1 - 1000");

            // Masīvs ar romiešu cipariem un to vērtībām.
            const RomanNumeral roman[] {
                {"M", 1000}, {"CM", 900},
                {"D",  500}, {"CD", 400},
                {"C",  100}, {"XC",  90},
                {"L",   50}, {"XL",  40},
                {"X",   10}, {"IX",   9},
                {"V",    5}, {"IV",   4},
                {"I",    1}
            };

            // Atkārtoti pievienojam lielākos iespējamos romiešu ciparus
            // līdz ievadītais cipars ticis konvertēts.
            std::string res;
            for (unsigned i = 0; i < 13; i++) {
                while((inputNum - roman[i].Value) >= 0) {
                    res += roman[i].Symbol;
                    inputNum -= roman[i].Value;
                }
            }

            // Paziņojam rezultātu
            std::cout << res << '\n' << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Nepienemami dati; " << e.what() << "\n" << std::endl;
        }
    }
}
