#include <forward_list>

void deleteMaxFirstLast(std::forward_list<int>& ints) {
    int first_val = ints.front();
    int last_val = first_val - 1;
    unsigned len = 0;

    // Find last value and length
    for (auto& i : ints) {
        last_val = i;
        len++;
    }

    // Remove first
    if (first_val > last_val) {
        ints.pop_front();
    }
    // Remove last
    else {
        auto iter = ints.before_begin();
        for (; len > 1; len--)
            iter++;

        ints.erase_after(iter);
    }
}
