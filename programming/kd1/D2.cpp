#include <list>
#include <limits>

void deleteSmallerAfter(std::list<int>& ints) {
    int prev = std::numeric_limits<int>::lowest();

    for (auto iter = ints.begin(); iter != ints.end(); ) {
        if (*iter < prev) {
            prev = *(iter--);
            iter++;
            iter = ints.erase(iter);
            iter--;
        }
        else {
            prev = *iter;
            iter++;
        }
    }
}
