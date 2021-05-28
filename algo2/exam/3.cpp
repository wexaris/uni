#include <list>
#include <map>

int moveOddsToEnd(std::list<int>& list) {
    std::map<int, int> pairNumCount;
    for (auto iter = list.begin(); iter != list.end(); iter++) {
        if (*iter % 2 == 0) {
            // Track pair number count
            pairNumCount[*iter] += 1;
        }
        else {
            auto prev = (--iter)++;

            // Look for pair number after odd
            auto finder = iter;
            for (; finder != list.end() && *finder % 2 != 0; finder++);
            // If there was none, stop looping
            if (finder == list.end())
                break;

            // Move odd to end
            list.splice(list.end(), list, iter, finder);

            iter = prev;
        }
    }
    return pairNumCount.size();
}

#include <iostream>

void print(const std::list<int>& list) {
    for (auto& e : list)
        std::cout << e << " ";
    std::cout << std::endl;
}

int main() {
    std::list<int> list{1,6,5,4,6,3,7,9};
    std::cout << moveOddsToEnd(list) << std::endl;
    print(list);
}
