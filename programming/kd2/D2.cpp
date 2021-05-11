#include <string>
#include <fstream>
#include <iostream>
#include <list>

struct Book {
    std::string Name;
    std::string Publisher;
    unsigned int Year;
    unsigned int Pages;
    unsigned int ISBNIndex; // 1-100000
};

bool book_compare(const Book& a, const Book& b) {
    return (a.ISBNIndex % 1100) < (b.ISBNIndex % 1100);
}

constexpr const char* IN_FILE = "books.txt";
constexpr const char* OUT_FILE = "books.bin";

int main() {
    // Open input text file
    std::ifstream in(IN_FILE);
    if (!in) {
        std::cout << "Failed to open input file!" << std::endl;
        return 1;
    }

    // Collect books from a file
    std::list<Book> books;
    for (int i = 0; i < 1000; i++) {
        // READ BOOK DATA
    }
    in.close();

    // Sort books
    books.sort(book_compare);


    // Open output binary file
    std::ofstream out(OUT_FILE, std::ios::binary);
    if (!out) {
        std::cout << "Failed to open output file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Write book data to binary
    for (auto& book : books) {
        auto name_len = book.Name.size();
        auto pub_len = book.Publisher.size();
        out.write((char*)&name_len, sizeof(book.Name));
        out.write(book.Name.data(), name_len);
        out.write((char*)&pub_len, sizeof(book.Publisher));
        out.write(book.Publisher.data(), pub_len);
        out.write((char*)&book.Year, sizeof(book.Year));
        out.write((char*)&book.Pages, sizeof(book.Pages));
        out.write((char*)&book.ISBNIndex, sizeof(book.ISBNIndex));
    }
    out.close();

    return 0;
}