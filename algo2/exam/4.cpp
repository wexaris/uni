#include <iostream>
#include <fstream>
#include <vector>

constexpr char* INPUT_FILE = "izdevumi.bin";

struct Article {
    std::string name;
    int type;
    int publishRate;
    char language;
    std::string publisher;
    int number;
};

std::string parseString(std::ifstream& in) {
    // Read string length data
    size_t len;
    in.read((char*)&len, sizeof(len));

    // Read string
    char* temp = new char[len + 1];
    in.read(temp, len);
    temp[len] = '\0';

    // Clean up
    std::string str = temp;
    delete[] temp;
    return str;
}

std::vector<Article> getArticles(const std::string& publisher) {
    std::ifstream in(INPUT_FILE, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Failed to open input file!" << std::endl;
        return {};
    }

    std::vector<Article> articles;
    while (in) {
        // Parse article from binary
        Article a;
        a.name = parseString(in);
        in.read((char*)&a.type, sizeof(a.type));
        in.read((char*)&a.publishRate, sizeof(a.publishRate));
        in.read((char*)&a.language, sizeof(a.language));
        a.publisher = parseString(in);
        in.read((char*)&a.number, sizeof(a.number));

        // Save matching articles
        if (a.publisher == publisher)
            articles.push_back(std::move(a));
    }
    return articles;
}

void print(const std::vector<Article>& list) {
    for (auto& e : list) {
        std::cout <<
            e.name << " " <<
            e.type << " " <<
            e.publishRate << " " <<
            e.language << " " <<
            e.publisher << " " <<
            e.number << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::string publisher;
    std::cout << "Izdeveja nosaukums: ";
    std::cin >> publisher;

    auto articles = getArticles(publisher);
    print(articles);
}
