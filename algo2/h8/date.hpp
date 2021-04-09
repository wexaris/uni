#pragma once

struct Date {
    int Year;
    int Month;
    int Day;

    inline std::string to_string() const {
        char buf[64];
        sprintf(buf, "%.4i/%.2i/%.2i", Year, Month, Day);
        return std::string(buf);
    }
};
