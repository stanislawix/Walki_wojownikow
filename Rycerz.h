#ifndef HK1_RYCERZ_H
#define HK1_RYCERZ_H
#include "Wojownik.h"

class Rycerz : public Wojownik {
public:
    Rycerz(std::string &imie, std::default_random_engine&, std::uniform_int_distribution<int>&, std::uniform_int_distribution<int>&);
    ~Rycerz();

    int getCios(std::default_random_engine &silniczek);

    int getMiecze();
    int getTiB();
    int getDrzewcowa();
    int getSztylety();
    void getAtrybuty(int* tablica);

    void setMiecze(int &m);
    void setTiB(int &m);
    void setDrzewcowa(int &m);
    void setSztylety(int &m);

    std::vector<int> getCiosy();
    void setCiosy(const std::vector<int> &ciosy_);

    bool zadajObrazenia(int &&pz);
    void print();

private:
    int miecze;
    int topory_i_bulawy;
    int drzewcowa;
    int sztylety;
    std::vector<int> ciosy;

};


#endif //HK1_RYCERZ_H
