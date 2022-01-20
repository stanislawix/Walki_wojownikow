#include "Skill.h"

Skill::Skill(std::string &nazwa, std::string &opis, char &archetyp, double* wagi) {
    // Konstruktor
    this->nazwa = nazwa;
    this->opis = opis;
    this->archetyp = archetyp;
    for(int i = 0; i<9; i++){
        this->wagi_atrubutow[i] = *(wagi+i);
    }
}

std::string Skill::getNazwa() {
    return this->nazwa;
}

std::string Skill::getOpis() {
    return this->opis;
}

char Skill::getArchetyp() const {
    return this->archetyp;
}

double *Skill::getWagi() {
    return this->wagi_atrubutow;
}

void Skill::print() {
    // Funkcja drukująca na ekran wszystkie informacje o danym skillu.
    std::cout << nazwa << ": " << opis << " - " << wagi_atrubutow[0] << " " << wagi_atrubutow[1] << " " <<
    wagi_atrubutow[2] << " " << wagi_atrubutow[3] << " " << wagi_atrubutow[4] << " " << wagi_atrubutow[5] << " " <<
    wagi_atrubutow[6] << " " << wagi_atrubutow[7] << " " << wagi_atrubutow[8] << std::endl;
}

int Skill::getDamage(int *atrybuty) {
    // Funkcja zwracająca zadane przez dany skill obrażenia, w zależności od atrybutów wojownika używającego skilla.
    int suma = 0;
    bool ok = true;
    for(int i=0; i<9; i++){
        if( (atrybuty+i) == nullptr ){
            ok = false;
            std::cout << "Nie podano prawidlowej tablicy int[9] z atrybutami postaci! Indeks nieprawidlowego elementu tablicy: " << i << "." << std::endl;
        }else if( *(atrybuty+i) >50 || *(atrybuty+i) <0 ){
            ok = false;
            std::cout << "Zle wartosci w tablicy int[9] z atrybutami postaci! Indeks nieprawidlowej wartosci: " << i << ". Nieprawidlowa wartosc: " << *(atrybuty+i) << std::endl;
        }
    }
    if(ok){
        for(int i=0; i<9; i++){
            suma += (int)(wagi_atrubutow[i] * (double)(atrybuty[i]));
        }
    }
    if(suma <= 0){
        std::cout << "Obrazenia wynosza " << suma << " xD" << std::endl;
    }
    suma = suma/3;
    return suma;
}

void Skill::setNazwa(std::string &nazwa) {
    this->nazwa = nazwa;
}

void Skill::setOpis(std::string &opis) {
    this->opis = opis;
}

void Skill::setArchetyp(char &archetyp) {
    // Funkcja pozwalająca zmienić archetyp skilla.
    if( archetyp == 'm' )
        archetyp = 'M';
    else if( archetyp == 'p')
        archetyp = 'P';
    else if( archetyp == 'r')
        archetyp = 'R';

    if( archetyp != 'M' && archetyp != 'P' && archetyp != 'R' ){
        std::cout << "BLAD: nie podano archetypu postaci, ktore moga korzystac z tworzonego skilla!" << std::endl;
    }else{
        this->archetyp = archetyp;
    }
}

void Skill::setWagi(double *wagi) {
    // Funkcja pozwalająca zmienić wagi atrybutów podczas obliczania zadawanych obrażeń.
    bool ok = true;
    for(int i=0; i<9; i++){
        if( (wagi+i) == nullptr ){
            ok = false;
            std::cout << "Nie podano prawidlowej tablicy int[9] z wagami atrybutow postaci! Indeks nieprawidlowego elementu tablicy: " << i << "." << std::endl;
        }else if( *(wagi+i) >10 || *(wagi+i) <0 ){
            ok = false;
            std::cout << "Zle wartosci w tablicy wag atrybutow skilla! Indeks nieprawidlowej wartosci: " << i << ". Nieprawidlowa wartosc: " << *(wagi+i) << std::endl;
        }
    }
    if(ok){
        for(int i=0; i<9; i++)
            this->wagi_atrubutow[i] = wagi[i];
    }

}