#include "Wojownik.h"

Wojownik::Wojownik(std::default_random_engine &silniczek, std::uniform_int_distribution<int> &przedzialek20, std::uniform_int_distribution<int> &przedzialek10) {
    // Konstruktor testowy
    this->imie = "Bezimienny wojownik";
    this->inteligencja = przedzialek20(silniczek);
    this->sila = przedzialek20(silniczek);
    this->sila_woli = przedzialek20(silniczek);
    this->zrecznosc = przedzialek20(silniczek);
    this->budowa = przedzialek20(silniczek);
    this->punkty_zycia = 100;
}

Wojownik::~Wojownik() = default; // Konstruktor wymagany dla utworzenia klas dziedziczących.

std::string Wojownik::getImie() {
    return imie;
}

int Wojownik::getInteligencja() {
    return inteligencja;
}

int Wojownik::getSila() {
    return sila;
}

int Wojownik::getZrecznosc() {
    return zrecznosc;
}

int Wojownik::getBudowa() {
    return budowa;
}

int Wojownik::getWola() {
    return sila_woli;
}

void Wojownik::setInteligencja(int &a){
    this->inteligencja = a;
}

void Wojownik::setSila(int &a){
    this->sila = a;
}

void Wojownik::setBudowa(int &a){
    this->budowa = a;
}

void Wojownik::setWola(int &a){
    this->sila_woli = a;
}

void Wojownik::setZrecznosc(int &a){
    this->zrecznosc = a;
}

void Wojownik::print(){
    // Funkcja drukująca na ekran informacje o wojowniku (nieużywana, gdyż nie ma wojowników klasy Wojownik, są tylko wojownicy klas pochodnych - mag, rycerz, polimorf).
    std::cout << this->imie << " " << this->sila << " " << this->inteligencja << " " << this->zrecznosc << " " << this->budowa << " " << this->sila_woli << std::endl;
}

void Wojownik::resetHP() {
    // Funkcja resetująca wartość punktów życia danego wojownika (używana pomiędzy walkami, przez zwycięzcach pojedynków).
    this->punkty_zycia = 100;
}
