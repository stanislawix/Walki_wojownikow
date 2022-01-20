#include "Rycerz.h"

Rycerz::Rycerz(std::string &imie, std::default_random_engine &silniczek, std::uniform_int_distribution<int> &przedzialek20, std::uniform_int_distribution<int> &przedzialek10) {
    //Konstruktor
    //miecze, topory_i_bulawy, drzewcowa, sztylety
    if(imie.length()<2)
        this->imie = "Bezimienny rycerz";
    else
        this->imie = imie;
    this->punkty_zycia = 100;
    this->inteligencja = przedzialek20(silniczek);
    this->sila = przedzialek20(silniczek);
    this->sila_woli = przedzialek20(silniczek);
    this->zrecznosc = przedzialek20(silniczek);
    this->budowa = przedzialek20(silniczek);
    this->miecze = przedzialek20(silniczek);
    this->topory_i_bulawy = przedzialek20(silniczek);
    this->drzewcowa = przedzialek20(silniczek);
    this->sztylety = przedzialek20(silniczek);

    for(int i=0; i<3; i++)
        this->ciosy.push_back(przedzialek10(silniczek)%5);
}

int Rycerz::getCios(std::default_random_engine &silniczek) {
    // Funkcja zwraca losowe ID (losuje wśród ciosów, które dany rycerz zna).
    std::uniform_int_distribution<int> przedzialek(0, ciosy.size()-1);
    return ciosy[przedzialek(silniczek)];
}

int Rycerz::getMiecze() {
    return this->miecze;
}

int Rycerz::getTiB() {
    return this->topory_i_bulawy;
}

int Rycerz::getDrzewcowa() {
    return this->drzewcowa;;
}

int Rycerz::getSztylety() {
    return this->sztylety;
}

void Rycerz::setMiecze(int &m) {
    this->miecze = m;
}

void Rycerz::setTiB(int &m) {
    this->topory_i_bulawy = m;
}

void Rycerz::setDrzewcowa(int &m) {
    this->drzewcowa = m;
}

void Rycerz::setSztylety(int &m) {
    this->sztylety = m;
}

std::vector<int> Rycerz::getCiosy() {
    return ciosy;
}

void Rycerz::print() {
    // Funkcja drukuje na ekran wszystkie informacje o rycerzu.
    std::cout << "Rycerz: " << this->imie << " " << this->inteligencja << " " << this->sila << " " << this->budowa << " " << this->sila_woli << " " << this->zrecznosc << " " << this->miecze << " " << this->topory_i_bulawy << " " << this->drzewcowa << " " << this->sztylety << std::endl;
}

void Rycerz::getAtrybuty(int* tablica) {
    // Funkcja przypisuje nowe wartości atrybutów z tablicy, do której wskaźnik podano jako argument.
    tablica[0] = this->inteligencja;
    tablica[1] = this->sila;
    tablica[2] = this->budowa;
    tablica[3] = this->sila_woli;
    tablica[4] = this->zrecznosc;
    tablica[5] = this->miecze;
    tablica[6] = this->topory_i_bulawy;
    tablica[7] = this->drzewcowa;
    tablica[8] = this->sztylety;
}


bool Rycerz::zadajObrazenia(int &&pz) {
    // Funkcja zadająca obrażenia wojownikowi, ponadto zwracająca true - jeśli to był śmiertelny cios.
    this->punkty_zycia -= pz;
    if(punkty_zycia<=0){
        return true;
    }else{
        return false;
    }
}


void Rycerz::setCiosy(const std::vector<int> &ciosy_) {
    // Funkcja dodaje nowe ciosy do puli ciosów znanych przez rycerza.
    for(int c : ciosy_){
        if(!(std::find(this->ciosy.begin(), this->ciosy.end(), c) != this->ciosy.end()))
            this->ciosy.emplace_back(c);
    }
}

Rycerz::~Rycerz() {
    // Destruktor

}
