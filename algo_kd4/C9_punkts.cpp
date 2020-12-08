#include "C9_punkts.h"
#include <iostream>

void Punkts::setPunkts(int x, int y) {
    this->x = x;
    this->y = y;
}

void Punkts::getPunkts(int& x, int& y) const {
    x = this->x;
    y = this->y;
}

void Punkts::increasePunkts(int d) {
    x += d;
    y += d;
}

void Punkts::print() const {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}