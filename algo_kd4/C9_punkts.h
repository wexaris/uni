#pragma once

class Punkts {
public:
    Punkts() = default;
    ~Punkts() = default;

    void setPunkts(int x, int y);
    void getPunkts(int& x, int& y) const;
    void increasePunkts(int d);
    void print() const;

private:
    int x = 0;
    int y = 0;
};