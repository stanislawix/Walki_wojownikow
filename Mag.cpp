#include "Mag.h"

Mag::Mag(std::string &imie, std::default_random_engine &silniczek, std::uniform_int_distribution<int> &przedzialek20, std::uniform_int_distribution<int> &przedzialek10) {
    //Konstruktor
    //ogien, woda, powietrze, ziemia
    if(imie.length()<2)
        this->imie = "Bezimienny mag";
    else
        this->imie = imie;
    this->punkty_zycia = 100;
    this->inteligencja = przedzialek20(silniczek);
    this->sila = przedzialek20(silniczek);
    this->sila_woli = przedzialek20(silniczek);
    this->zrecznosc = przedzialek20(silniczek);
    this->budowa = przedzialek20(silniczek);
    this->magia_ognia = przedzialek20(silniczek);
    this->magia_wody = przedzialek20(silniczek);
    this->magia_powietrza = przedzialek20(silniczek);
    this->magia_ziemi = przedzialek20(silniczek);

    for(int i=0; i<3; i++)
        this->zaklecia.push_back(przedzialek10(silniczek)%5);
}

int Mag::getZaklecie(std::default_random_engine &silniczek) {
    // Funkcja zwraca losowe ID zaklęcia (losuje wśród zaklęć, które dany mag zna).
    std::uniform_int_distribution<int> przedzialek(0, zaklecia.size()-1);
    return zaklecia[przedzialek(silniczek)];
}

int Mag::getMagia_Ognia() {
    return magia_ognia;
}

int Mag::getMagia_Wody() {
    return magia_wody;
}

int Mag::getMagia_Powietrza() {
    return magia_powietrza;
}

int Mag::getMagia_Ziemi() {
    return magia_ziemi;
}

void Mag::setMagia_Ognia(int &m) {
    this->magia_ognia = m;
}

void Mag::setMagia_Wody(int &m) {
    this->magia_wody = m;
}

void Mag::setMagia_Powietrza(int &m) {
    this->magia_powietrza = m;
}

void Mag::setMagia_Ziemi(int &m) {
    this->magia_ziemi = m;
}

std::vector<int> Mag::getZaklecia() {
    return zaklecia;
}

void Mag::print() {
    // Funkcja drukuje na ekran wszystkie informacje o magu.
    std::cout << "Mag: " << this->imie << " " << this->inteligencja << " " << this->sila << " " << this->budowa << " " << this->sila_woli << " " << this->zrecznosc << " " << this->magia_ognia << " " << this->magia_wody << " " << this->magia_powietrza << " " << this->magia_ziemi << std::endl;
}

void Mag::getAtrybuty(int* tablica) {
    // Funkcja przypisuje nowe wartości atrybutów z tablicy, do której wskaźnik podano jako argument.
    tablica[0] = this->inteligencja;
    tablica[1] = this->sila;
    tablica[2] = this->budowa;
    tablica[3] = this->sila_woli;
    tablica[4] = this->zrecznosc;
    tablica[5] = this->magia_ognia;
    tablica[6] = this->magia_wody;
    tablica[7] = this->magia_powietrza;
    tablica[8] = this->magia_ziemi;
}

void Mag::setZaklecia(const std::vector<int> &zaklecia_) {
    // Funkcja dodaje nowe zaklęcia do puli zaklęć znanych przez maga.
    for(int z : zaklecia_){
        if(std::find(this->zaklecia.begin(), this->zaklecia.end(), z) != this->zaklecia.end())
            this->zaklecia.emplace_back(z);
    }
}

bool Mag::zadajObrazenia(int &&pz) {
    // Funkcja zadająca obrażenia wojownikowi, ponadto zwracająca true - jeśli to był śmiertelny cios.
    this->punkty_zycia -= pz;
    if(punkty_zycia<=0){
        return true;
    }else{
        return false;
    }
}

Mag::~Mag() {

}
