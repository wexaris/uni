#include <iostream>

int to_num(char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    return -1;
}

void remove_one(char* str) {
    unsigned i = 0;
    for (; str[i] != '\0'; i++)
        str[i] = str[i + 1];

    str[i - 1] = '\0';
}

void digits_descending(char* str) {
    int last_num = -1;

    for (; *str != '\0'; str++) {
        int curr_num = to_num(*str);

        if (last_num == -1) {
            last_num = curr_num;
            continue;
        }

        if (curr_num != -1) {
            if (curr_num >= last_num) {
                remove_one(str);
                str--;
            }
            else
                last_num = curr_num;
        }
        else { last_num = -1; }
    }
}

#include <string.h>

int main() {
    char* str = strdup("A231-987x4564.");
    digits_descending(str);
    std::cout << str << std::endl;
}