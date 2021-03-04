#include <iostream>

template <typename F>
void for_each_digit(int x, const F func) {
    if(x >= 10)
       for_each_digit(x / 10, func);

    func(x % 10);
}

unsigned count_ones(unsigned x) {
    unsigned count = 0;

    for_each_digit(x, [&](unsigned d){
        if (d == 1) {
            count++;
        }
    });

    return count;
}

int main() {
    unsigned nums[3];
    std::cout << "Ievadiet 3 skaitlus: ";
    std::cin >> nums[0] >> nums[1] >> nums[2];

    unsigned xc = count_ones(nums[0]);
    unsigned yc = count_ones(nums[1]);
    unsigned zc = count_ones(nums[2]);

    // Sakārtojam masīvu pēc vieninieku skaita
    if (yc < xc) {
        unsigned tmp = nums[0];
        nums[0] = nums[1];
        nums[1] = tmp;
    }
    if (zc < yc) {
        unsigned tmp = nums[1];
        nums[1] = nums[2];
        nums[2] = tmp;
    }
    if (yc < xc) {
        unsigned tmp = nums[0];
        nums[0] = nums[1];
        nums[1] = tmp;
    }

    std::cout << "Visvairak vieninieki: " << nums[2] << std::endl;
}