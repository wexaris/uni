/*******************************************
Rainers Vorza, rv20039
C7. Dots masīvs A(m,n), kas sastāv no veseliem skaitļiem. Atrast četrus
skaitļus h,i,j,k, kas apzīmē apakšmatricu, kuras elementu kopsumma ir vislielākā
(h,i apzīmē apakšmatricas kreiso augšējo stūri, bet j,k - labo apakšējo).
Programma izveidota: 18/11/2020
*******************************************/

// Rezultātu tabula:
// ----------------------------------------------
//  Matrica | CPPRezultāts | Paredzēts  | Sakrīt
// ----------------------------------------------
//  -10  1  |  (0,1)(1,1)  | (0,1)(1,1) |   x
//    1  1  |              |            |

#include <iostream>
#include <stdlib.h>   // srand, rand
#include <time.h>     // time

// Apakšmatricas pozīcija
struct Rect {
    unsigned top_x, top_y;
    unsigned bot_x, bot_y;
};

// Iegūst apakšmatricas elementu summu
int SubMatrixSum(int* matrix, unsigned cols, const Rect& rect) {
    int sum = 0;
    for (unsigned i = rect.top_y; i <= rect.bot_y; i++)
        for (unsigned j = rect.top_x; j <= rect.bot_x; j++)
            sum += matrix[i * cols + j];
    return sum;
}

int main() {
    // Turpinam akārtot programmas darbību
    bool run = true;
    while (run)
    {
        // Pieprasām matricas izmēru no lietotāja
        unsigned rows, cols;
        std::cout << "Matricas izmeri: ";
        std::cin >> rows >> cols;

        int matrix[rows * cols]; // Pieklūst [i][j] ar matrix[i * cols + j]

#if 1
        // Prasam lietotājam aipildīt matricu
        for (unsigned i = 0; i < rows; i++) {
            for (unsigned j = 0; j < cols; j++) {
                std::cout << "Elements " << i << "," << j << ": ";
                std::cin >> matrix[i * cols + j];
            }
        }
#else
        // Piepildam matricu ar cipariem [-100; 100]
        srand (time(NULL));
        for (unsigned i = 0; i < rows * cols; i++)
            matrix[i] = rand() % (200 + 1) - 100;
#endif

        // Izprintējam matricu
        for (unsigned i = 0; i < rows; i++) {
            for (unsigned j = 0; j < cols; j++)
                std::cout << matrix[i * cols + j] << " ";
            std::cout << std::endl;
        }

        // Apakšmatricas ar lielāko summu pozīcija un vērtiba
        Rect max_pos;
        int max_sum = INT_MIN;

        // Apskatam katras iespejamās apakšmatricas pozīciju
        // Pozīcija (h,i) ir augšējais kreisais stūris
        for (unsigned h = 0; h < cols; h++) {
            for (unsigned i = 0; i < rows; i++) {
                // Pozīcija (j,k) ir apakšējais labais stūris
                // Neapskatām pozīcijas pirms pašreizēja (h,i)
                for (unsigned j = h; j < cols; j++) {
                    for (unsigned k = i; k < rows; k++) {

                        // Iegūstam pašreizējās apakšmatricas elementu summu
                        Rect pos = Rect{h, i, j, k};
                        int sum = SubMatrixSum(matrix, cols, pos);

                        // Saglabajam šo summu, ja tā ir lielāka par pašreizējo lielāko
                        if (sum > max_sum) {
                            max_sum = sum;
                            max_pos = pos;
                        }
                    }
                }
            }
        }

        // Izprintējam rezultātu
        std::cout << "Apaksmatrica ar lielako elementu summu: (" <<
            max_pos.top_x << ", " << max_pos.top_y << ") (" <<
            max_pos.bot_x << ", " << max_pos.bot_y << ")" << std::endl;
        std::cout << "Summa: " << max_sum << std::endl;

        // Prasam, vai atkārtot
        std::cout << "Atkārtot? (1/0): ";
        std::cin >> run;
    }
}