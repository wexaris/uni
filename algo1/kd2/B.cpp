#include <iostream>

bool funkcija(int& a, int& b, int& c, double& d) {
    // Pārbaudi vai a,b,c vinādi
    bool ret = a == b && b == c;

    // Saglabā vidējo aritmētisko
    d = (a + b + c) / 3.0;

    // Lielāko aizvieto ar pārējo summu
    if (a > b && a > c)      a = b + c;
    else if (b > a && b > c) b = a + c;
    else                     c = a + b;

    return ret;
}

int main() {
    int a, b, c;
    double d;
    std::cin >> a >> b >> c;

    std::cout << "ret: " << funkcija(a, b, c, d) << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;
}