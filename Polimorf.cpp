#include "Polimorf.h"

Polimorf::Polimorf(std::string &imie, std::default_random_engine &silniczek, std::uniform_int_distribution<int> &przedzialek20, std::uniform_int_distribution<int> &przedzialek10) {
    // Konstruktor
    //przemiany, odpornosc, przywolywanie, zywioly
    if(imie.length()<2)
        this->imie = "Bezimienny polimorf";
    else
        this->imie = imie;
    this->punkty_zycia = 100;
    this->inteligencja = przedzialek20(silniczek);
    this->sila = przedzialek20(silniczek);
    this->sila_woli = przedzialek20(silniczek);
    this->zrecznosc = przedzialek20(silniczek);
    this->budowa = przedzialek20(silniczek);
    this->przemiany = przedzialek20(silniczek);
    this->odpornosc = przedzialek20(silniczek);
    this->przywolywanie = przedzialek20(silniczek);
    this->zywioly = przedzialek20(silniczek);

    for(int i=0; i<3; i++)
        this->umiejetnosci.push_back(przedzialek10(silniczek)%5);
}

int Polimorf::getUmiejetnosc(std::default_random_engine &silniczek) {
    // Funkcja zwraca losowe ID umiejętności (losuje wśród umiejętności, które dany polimorf zna).
    std::uniform_int_distribution<int> przedzialek(0, umiejetnosci.size()-1);
    return umiejetnosci[przedzialek(silniczek)];
}

int Polimorf::getPrzywolywanie() {
    return przywolywanie;
}

int Polimorf::getOdpornosc() {
    return odpornosc;
}

int Polimorf::getPrzemiany() {
    return przemiany;
}

int Polimorf::getZywioly() {
    return zywioly;
}

void Polimorf::setPrzywolywanie(int &m) {
    this->przywolywanie = m;
}

void Polimorf::setOdpornosc(int &m) {
    this->odpornosc = m;
}

void Polimorf::setPrzemiany(int &m) {
    this->przemiany = m;
}

void Polimorf::setZywioly(int &m) {
    this->zywioly = m;
}

std::vector<int> Polimorf::getUmiejetnosci() {
    return umiejetnosci;
}

void Polimorf::print() {
    // Funkcja drukuje na ekran wszystkie informacje o polimorfie.
    std::cout << "Polimorf: " << this->imie << " " << this->inteligencja << " " << this->sila << " " << this->budowa << " " << this->sila_woli << " " << this->zrecznosc << " " << this->przemiany << " " << this->odpornosc << " " << this->przywolywanie << " " << this->zywioly << std::endl;
}

void Polimorf::getAtrybuty(int* tablica) {
    // Funkcja przypisuje nowe wartości atrybutów z tablicy, do której wskaźnik podano jako argument.
    tablica[0] = this->inteligencja;
    tablica[1] = this->sila;
    tablica[2] = this->budowa;
    tablica[3] = this->sila_woli;
    tablica[4] = this->zrecznosc;
    tablica[5] = this->przemiany;
    tablica[6] = this->odpornosc;
    tablica[7] = this->przywolywanie;
    tablica[8] = this->zywioly;
}


void Polimorf::setUmiejetnosci(const std::vector<int> &umiejetnosci_) {
    // Funkcja dodaje nowe umiejętności do puli umiejętności znanych przez polimorfa.
    for(int u : umiejetnosci_){
        if(std::find(this->umiejetnosci.begin(), this->umiejetnosci.end(), u) != this->umiejetnosci.end())
            this->umiejetnosci.emplace_back(u);
    }
}

bool Polimorf::zadajObrazenia(int &&pz) {
    // Funkcja zadająca obrażenia wojownikowi, ponadto zwracająca true - jeśli to był śmiertelny cios.
    this->punkty_zycia -= pz;
    if(punkty_zycia<=0){
        return true;
    }else{
        return false;
    }
}

Polimorf::~Polimorf() {
    // Destruktor

}

