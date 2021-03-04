// 4. Uzdevums (II) - kopu šķēlums
// Ievadi no klaviatūras 50 naturālus skaitļus, pēc tam vēlreiz
// citus 50 naturālus skaitļus. Izdrukāt bez atkārtojumiem tos skaitļus,
// kas sastopas abās skaitļu virknēs.
//
// Rainers Vorza
// rv20039

#include <iostream>
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

// Parbauda vai masivs satur noteiktu vertibu
// Apskata indeksus [0; len)
bool contains(unsigned* arr, unsigned len, unsigned item) {
    for (unsigned k = 0; k < len; k++)
        if (arr[k] == item)
            return true;
    return false;
}

int main() {
    // Divas skaitlu virknes
    unsigned nums1[50] = {0};
    unsigned nums2[50] = {0};
    // Virkene kopigiem skaitliem
    unsigned match[50] = {0}; // 50 jo tas ir maksimalais skaits, kas varetu sakrirst
    unsigned idx = 0;

#if 1
    // Prasam lietotajam aizpildit virknes ar skaitliem
    for (int i = 0; i < 50; i++) {
        std::cout << "Virkne 1, skaitlis " << i << ": ";
        std::cin >> nums1[i];
    }
    for (int i = 0; i < 50; i++) {
        std::cout << "Virkne 2, skaitlis " << i << ": ";
        std::cin >> nums2[i];
    }
#else
    // Piepildam virknes ar skaitliem, lai tas nav jadara lietotajam
    srand (time(NULL));
    for (int i = 0; i < 50; i++) {
        nums1[i] = rand() % 100 + 1;
        nums2[i] = rand() % 100 + 1;
    }
#endif

    // Pazinojam par virknu sastavu
    std::cout << "Virkne 1: ";
    for (int i = 0; i < 50; i++)
        std::cout << nums1[i] << " ";
    std::cout << std::endl;

    std::cout << "Virkne 2: ";
    for (int i = 0; i < 50; i++)
        std::cout << nums2[i] << " ";
    std::cout << std::endl;

    // Meklejam kopigas vertibas
    // Saglabajam tas `match` masiva
    for (unsigned i = 0; i < 50; i++) {
        for (unsigned j = 0; j < 50; j++) {
            if (nums1[i] == nums2[j])
                // Nelaujam divreiz pievienot to pasu skaitli
                if (!contains(match, idx, nums1[i]))
                    match[idx++] = nums1[i];
        }
    }

    // Pazinojam par kopigajiem elementiem
    std::cout << "Kopigas vertibas: ";
    for (int i = 0; i < idx; i++)
        std::cout << match[i] << " ";
    std::cout << std::endl;
}