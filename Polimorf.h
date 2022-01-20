#ifndef HK1_POLIMORF_H
#define HK1_POLIMORF_H
#include "Wojownik.h"

class Polimorf : public Wojownik {
public:
    Polimorf(std::string &imie, std::default_random_engine&, std::uniform_int_distribution<int>&, std::uniform_int_distribution<int>&);
    ~Polimorf();

    int getUmiejetnosc(std::default_random_engine &silniczek);
    int getPrzywolywanie();
    int getOdpornosc();
    int getPrzemiany();
    int getZywioly();
    void getAtrybuty(int* tablica);

    void setPrzywolywanie(int &m);
    void setOdpornosc(int &m);
    void setPrzemiany(int &m);
    void setZywioly(int &m);

    std::vector<int> getUmiejetnosci();
    void setUmiejetnosci(const std::vector<int> &umiejetnosci_);

    bool zadajObrazenia(int &&pz);
    void print();

private:
    int przywolywanie;
    int odpornosc;
    int przemiany;
    int zywioly;
    std::vector<int> umiejetnosci;
};


#endif //HK1_POLIMORF_H
