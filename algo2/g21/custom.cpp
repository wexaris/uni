/*******************************************
Rainers Vorza, rv20039

Izveidot divas programmas valodā C++, kas strādā ar vērtību virkni divos dažādos veidos:
  1) to realizējot kā vienvirziena saistīto sarakstu, izmantojot dinamiskas datu struktūras,
  2) izmantojot STL::list konteineru.
Abās realizācijās ir jāizveido prasītā specifiskā vērtību virknes apstrādes funkcija un
jānodemonstrē tā darbībā, cita starpā parādot gan sākotnējās, gan rezultējošās vērtības.
Abās programmās:
  a) jābūt iespējai ievadīt saraksta elementus (izveidot patvaļīgu sarakstu),
  b) jāpielieto uzrakstītā funkcija sarakstam,
  c) jāizdrukā saraksts pēc funkcijas darbības.
  d) beigās jāiznīcina saraksts - korekti jāatbrīvo izdalītā atmiņa(lietojot delete vai clear).
Sīkākas prasības sk. Laboratorijas darbu noteikumos.

G21. Uzrakstīt funkciju, kas no dotā saraksta izveido jaunu sarakstu tā,
lai jaunajā sarakstā būtu visas vērtības no dotā saraksta un izveidotajā
sarakstā nebūtu elementu ar vienādām vērtībām.

Programma izveidota: 2021/04/08
*******************************************/

#include <iostream>
#include <sstream>

// Print the elements of any iterable container
template<class Cont>
void print(const Cont& container) {
    for (const auto& item : container)
        std::cout << item << " ";
    std::cout << std::endl;
}

////////////////////////////////////////////////////////////////
// Program using custom forward list implementation

#include "forward_list.hpp"

// Modifies the given list and removes any duplicate values
ForwardList<std::string> copy_without_duplicates(const ForwardList<std::string>& list) {
    ForwardList<std::string> new_list;
    auto iter = new_list.before_begin();

    for (const auto& item : list) {
        // Check if already exists
        for (const auto& added : new_list)
            if (item == added)
                goto exists;

        // Insert value into new list
        iter = new_list.insert_after(iter, item);

exists:;
    }

    return new_list;
}

int main() {
    while (true) {
        // Collect input
        std::cout << "Enter values (space seperated; leave empty to exit): ";
        std::string input;
        std::getline(std::cin, input);
        if (input.empty())
            break;

        // Create list and iterator
        ForwardList<std::string> list;
        auto iter = list.cbefore_begin(); // For inserting new values

        // Split into words and add to list
        std::string word;
        std::stringstream ss(input);
        while (ss >> word) {
            iter = list.insert_after(iter, word); // ForwardList doesn't support push_back
        }

        print(list);

        // Create new list without duplicates
        list = copy_without_duplicates(list);

        print(list);
        std::cout << std::endl;

        // Remove list items
        list.clear();
    }

    return EXIT_SUCCESS;
}
