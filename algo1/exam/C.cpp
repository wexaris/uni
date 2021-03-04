#include <iostream>

unsigned min_max_dif(unsigned* matrix, unsigned rows, unsigned cols) {
    unsigned min = matrix[0], max = matrix[0];

    for (unsigned i = 0; i < cols; i++) {
        for (unsigned j = 0; j < rows; j++) {

            if (matrix[i * cols + j] < min)
                min = matrix[i * cols + j];

            if (matrix[i * cols + j] > max)
                max = matrix[i * cols + j];
        }
    }

    std::cout << min << " " << max << std::endl;

    return max - min;
}

int main() {
    // Pieprasām matricas izmēru no lietotāja
    unsigned rows, cols;
    std::cout << "Matricas izmeri: ";
    std::cin >> rows >> cols;

    unsigned matrix[rows * cols]; // Pieklūst [i][j] ar matrix[i * cols + j]

    // Prasam lietotājam aipildīt matricu
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            std::cout << "Elements " << i << "," << j << ": ";
            std::cin >> matrix[i * cols + j];
        }
    }

    unsigned dif = min_max_dif(matrix, rows, cols);

    std::cout << "Starpība starp lielāko un mazāko skaitli: " << dif << std::endl;
}