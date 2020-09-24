/*******************************************
Rainers Vorza, rv20039
A5. Dots naturāls skaitlis n. Izdrukāt skaitli, kurš iegūts no dotā skaitļa, izmetot ciparu k.
(Piemēram, ja n=12025 un k=2, jāiegūst 105). Skaitļa dalīšana ciparos jāveic skaitliski.
Programma izveidota: 17/09/2020
*******************************************/

// Rezultātu tabula:
//    n   |  k  |   CPPRezultāts   |   PyRezultāts    |    Paredzēts     | Sakrīt
// -------|-----|------------------|------------------|------------------|--------
//  12025 | 2   |              105 |              105 |              105 |   X
//    420 | 5   |              420 |              420 |              420 |   X
//   2020 | 2   |                0 |                0 |                0 |   X
//    555 | 5   |                - |                - |                - |   X
//      0 | 0   |                - |                - |                - |   X
//      5 |     | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
//        | 5   | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
//    txt | 5   | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
//      5 | txt | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
//    txt | txt | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
//    txt |     | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
//        | txt | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X

#include <iostream>
#include <string>
#include <algorithm> // remove_if()
#include <cmath>     // pow()

int main() {
    std::string inputStr;  // Ievadītais teksts
    std::string numberStr; // Naturālā skaitļa teksts
    std::string removeStr; // Izņemamā cipara teksts
    size_t inputNum;       // Naturalais skaitlis (uzd. 'n')
    int removeNum;         // Izņemamais cipars   (uzd. 'k')

    std::cout << "Ievadiet ENTER lai beigtu\n";

    while (true) {
        // Saņemam naturālo un izņemamo skaitli no lietotāja.
        // Izmantojam getline(), jo >> neļauj ievadīt tukšu rindu.
        // Ja ir tukšums, apturam programmu.
        std::cout << "Ievadiet naturālu skaitli un izņemamo ciparu: ";
        getline(std::cin, inputStr);
        if (inputStr.empty())
            return EXIT_SUCCESS;

        // Sadalam ievadīto tekstu
        numberStr = inputStr.substr(0, inputStr.find(' '));
        removeStr = inputStr.substr(numberStr.length());

        try {
            // Pārliecinamies, ka skaitļa teksts nav tukšs
            if (numberStr.empty())
                throw std::runtime_error("ievadītais nav naturāls skaitlis");
            // Ja ievadīts negatīvs skaitlis, stoull() atgriež maksimālo vērtību,
            // tāpēc mēs paši pārbaudam vai visi char ir decimāli pirms lietojam stoull().
            for (char c : numberStr) {
                if (!isdigit(c)) {
                    // Izmantojam throw, lai ērti izlaistu tālāko kodu un
                    // reizē paziņotu par sliktiem datiem.
                    throw std::runtime_error("ievadītais nav naturāls skaitlis");
                }
            }
            inputNum = stoull(numberStr); // Pārplūdes gadījumā met izņēmumu

            // Atbrīvojamies no atstarpēm izņemamajā tekstā.
            removeStr.erase(std::remove_if(removeStr.begin(), removeStr.end(), ::isspace), removeStr.end());
            // Pārliecinamies, ka izņemamais teksts satur tikai vienu ciparu.
            if (removeStr.length() != 1 || !isdigit(removeStr[0]))
                throw std::runtime_error("izņemamais nav viencipara skaitlis");
            removeNum = stoull(removeStr); // Pārplūdes gadījumā met izņēmumu

            // Pārbaudam visus naturālā skaitļa ciparus, pievienojot tos
            // rezultāta skaitlim, ja tie nesakrīt ar izņemamo ciparu.
            size_t res = 0;
            bool hasVal = false;
            for (size_t i = 0; inputNum != 0; ) { // Izmantojam 'i' lai sekotu līdzi nākamā cipara kāpinātājam
                int digit = inputNum % 10;
                inputNum /= 10;

                if (digit != removeNum) {
                    res += digit * pow(10, i);
                    hasVal = true;
                    i++;             // Palielinam 'i' tikai, ja pievinojām ciparu rezultātam
                }
            }

            // Paziņojot rezultātu, atšķiram ievadītu nulli no tukšas ciparu virknes.
            if (hasVal) std::cout << std::to_string(res) << '\n' << std::endl;
            else        std::cout << "-\n" << std::endl;
        }
        catch (std::exception& e) {
            std::cerr << "Nepieņemami dati; " << e.what() << "\n" << std::endl;
        }
    }
}