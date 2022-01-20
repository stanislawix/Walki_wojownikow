#ifndef HK1_WOJOWNIK_H
#define HK1_WOJOWNIK_H
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

class Wojownik {
public:
    Wojownik() = default;
    Wojownik(std::default_random_engine&, std::uniform_int_distribution<int>&, std::uniform_int_distribution<int>&);
    ~Wojownik();
    std::string getImie();
    int getInteligencja();
    int getSila();
    int getZrecznosc();
    int getBudowa();
    int getWola();
    void setInteligencja(int &a);
    void setSila(int &a);
    void setZrecznosc(int &a);
    void setBudowa(int &a);
    void setWola(int &a);

    void print();

    void resetHP();
    //bool zadajObrazenia(int &&pz);

protected:
    std::string imie;
    int punkty_zycia;
    int inteligencja;
    int sila;
    int zrecznosc;
    int budowa;
    int sila_woli;

private:

};


#endif //HK1_WOJOWNIK_H
