#ifndef HK1_MAG_H
#define HK1_MAG_H
#include "Wojownik.h"

class Mag : public Wojownik {
public:
    Mag(std::string &imie, std::default_random_engine&, std::uniform_int_distribution<int>&, std::uniform_int_distribution<int>&);
    ~Mag();

    int getZaklecie(std::default_random_engine&);

    int getMagia_Ognia();
    int getMagia_Wody();
    int getMagia_Powietrza();
    int getMagia_Ziemi();
    void getAtrybuty(int* tablica);


    void setMagia_Ognia(int &m);
    void setMagia_Wody(int &m);
    void setMagia_Powietrza(int &m);
    void setMagia_Ziemi(int &m);

    std::vector<int> getZaklecia();
    void setZaklecia(const std::vector<int> &zaklecia_);

    bool zadajObrazenia(int &&pz);
    void print();

private:
    int magia_ognia;
    int magia_wody;
    int magia_powietrza;
    int magia_ziemi;
    std::vector<int> zaklecia;

};

#endif //HK1_MAG_H
