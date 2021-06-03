/*******************************************
Rainers Vorza, rv20039

GG – STL list un saistītais saraksts ar izņēmumsituāciju apstrādi un vienībtestēšanu**.

* atrisināt uzdevumu G divos veidos:
  a) izmantojot dinamiskas datu struktūras (saistīto sarakstu vtml.),
  b) izmantojot STL::list konteineru.

** tas pats uzdevums, kas G, bet tā risinājums (a) jāpapildina ar divām lietām:
  1) vismaz viena no datu pārbaudēm jārealizē, izmantojot izņēmumsituāciju apstrādes
     (exception handling) mehānismu,
  2) vismaz viena funkcija (vēlams, galvenā) ir jānotestē, izmantojot vienībtestēšanu,
     kur attiecīgā funkcija būtu jāpārbauda uz vismaz trīs dažādiem nosacījumiem;
     šim nolūkam, kā minimums, ir nepieciešams:
        (1) šo funkciju iznest ārā citā failā (nekā funkcija main),
        (2) izveidot otru projektu speciāli šīs funkcijās testēšanai
            (tātad, kopā būs divi projekti, parastais, kas izmantos funkciju, otrais, kas testēs).

Papildus norāde: šādam vienībtestēšanas projektam daļēji atbilst iepriekšējā
semestra pēdējais laboratorijas darbs (ar klasēm) ar cieti iekodētu main funkciju.

Programma izveidota: 2021/06/01
*******************************************/

#include <iostream>
#include <sstream>
#include "forward_list.hpp"
#include "util.hpp"

////////////////////////////////////////////////////////////////
// Program using ForwardList<T>

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
