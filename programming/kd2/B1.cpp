#include <string>
#include <iostream>

class Gramata {
public:
    Gramata(const std::string& nosk, unsigned int lpp) :
        nosaukums(nosk), lappuses(lpp) {}

    virtual ~Gramata() = default;

    virtual void print() const {
        std::cout << nosaukums << " (" << lappuses << "lpp)" << std::endl;
    }

protected:
    std::string nosaukums;
    unsigned int lappuses;
};

class MacibuGramata : public Gramata {
public:
    MacibuGramata(const std::string& nosk, unsigned int lpp, const std::string* prieksm) :
        Gramata(nosk, lpp)
    {
        for (int i = 0; i < 3; i++) {
            prieksmeti[i] = prieksm[i];
        }
    }

    ~MacibuGramata() {}

    virtual void print() const override {
        std::cout << nosaukums << " (" << lappuses << "lpp)" << std::endl;
        std::cout << "Prieksmeti: ";
        for (auto& p : prieksmeti) {
            std::cout << p << ", ";
        }
        std::cout << std::endl;
    }

private:
    std::string prieksmeti[3];
};

int main() {
    Gramata g("gramata", 5);
    g.print();

    Gramata* dg = new Gramata("dyn gramata", 15);
    dg->print();
    delete dg;

    std::string prieksmeti[3] = { "Mat", "Ang", "Fiz" };

    MacibuGramata mg("macibu gramata", 10, prieksmeti);
    mg.print();

    MacibuGramata* dmg = new MacibuGramata("dyn macibu gramata", 20, prieksmeti);
    dmg->print();
    delete dmg;

    return 0;
}