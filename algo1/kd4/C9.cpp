#include "C9_punkts.h"
#include <assert.h>

int main() {
    int x, y;

    Punkts p1;
    p1.setPunkts(-1, 1);
    p1.increasePunkts(1);
    p1.print();
    p1.getPunkts(x, y);
    assert(x == 0);
    assert(y == 2);

    Punkts* p2 = new Punkts();
    p2->setPunkts(-20, 6);
    p2->increasePunkts(-5);
    p2->print();
    p2->getPunkts(x, y);
    assert(x == -25);
    assert(y == 1);
    delete p2;
}
