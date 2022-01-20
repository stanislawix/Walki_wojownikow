#include <iostream>
#include <fstream>
#include <sstream>
#include "Wojownik.h"
#include "Mag.h"
#include "Rycerz.h"
#include "Polimorf.h"
#include "Skill.h"

void dodaj_skill (std::vector<Skill> &skille, std::string &nazwa, std::string &opis, char &archetyp, double* wagi){
    // Funkcja konstruuje obiekt Skill o podanych właściwościach i wsadza go do wektora skille.

    bool ok = true;

    if( archetyp == 'm' )
        archetyp = 'M';
    else if( archetyp == 'p')
        archetyp = 'P';
    else if( archetyp == 'r')
        archetyp = 'R';

    if( archetyp != 'M' && archetyp != 'P' && archetyp != 'R' ){
        ok = false;
        std::cout << "BLAD: nie podano archetypu postaci, ktore moga korzystac z tworzonego skilla!" << std::endl;
    }

    if(ok){
        for(int i=0; i<9; i++){
            if( (wagi+i) == nullptr ){
                ok = false;
                std::cout << "Nie podano prawidlowej tablicy int[9] z wagami atrybutow postaci! Indeks nieprawidlowego elementu tablicy: " << i << "." << std::endl;
            }else if( *(wagi+i) >10 || *(wagi+i) <0 ){
                ok = false;
                std::cout << "Zle wartosci w tablicy wag atrybutow skilla! Indeks nieprawidlowej wartosci: " << i << ". Nieprawidlowa wartosc: " << *(wagi+i) << std::endl;
            }
        }
    }

    if(ok) {
        skille.emplace_back(nazwa, opis, archetyp, wagi);
        std::cout << "Dodano skill: " << archetyp << " " << nazwa << std::endl;
    }
}

void wczytaj_skille (std::vector<Skill> &v_ciosy, std::vector<Skill> &v_zaklecia, std::vector<Skill> &v_umiejetnosci, const std::string &filename = "../skille.txt"){
    // Funkcja wczytuje obiekty klasy Skill z pliku do odpowiednich wektorów, w zależności od archetypu.

    std::ifstream plik(filename);
    std::string wers, nazwa, opis;
    char znak = ';';
    char archetyp;
    double wagi[9]; //INT, SI, BUD, WOL, ZRE, 1, 2, 3, 4
    int index1=0, index2=0;
    std::cout << "WCZYTYWANIE SKILLI" << std::endl;
    int liczba_skilli = 0;
    if(plik.good()){
        while (std::getline(plik, wers))
        {
            archetyp = wers[0];
            index1 = 2;

            index2 = wers.find_first_of(znak, index1);
            nazwa = wers.substr(index1, index2-index1);
            index1 = index2+1;
            index2 = wers.find_first_of(znak, index1);
            opis = wers.substr(index1, index2-index1);
            index1 = index2+1;

            for(int i = 0; i<9; i++){
                index2 = wers.find_first_of(znak, index1);
                wagi[i] = std::stod(wers.substr(index1, index2-index1));
                index1 = index2+1;
            }

            if( archetyp == 'm' )
                archetyp = 'M';
            else if( archetyp == 'p')
                archetyp = 'P';
            else if( archetyp == 'r')
                archetyp = 'R';

            if(archetyp == 'R') {
                dodaj_skill(v_ciosy, nazwa, opis, archetyp, wagi);
                liczba_skilli++;
            }else if(archetyp == 'M') {
                dodaj_skill(v_zaklecia, nazwa, opis, archetyp, wagi);
                liczba_skilli++;
            }else if(archetyp == 'P') {
                dodaj_skill(v_umiejetnosci, nazwa, opis, archetyp, wagi);
                liczba_skilli++;
            }else{
                std::cout << "BLAD: nie podano archetypu postaci, ktore moga korzystac z tworzonego skilla!" << std::endl;
            }

        }
        std::cout << "WCZYTYWANIE SKILLI ZAKONCZONE ( " << liczba_skilli << " skilli )" << std::endl;
    }else{
        std::cout << "!NIE MOZNA OTWORZYC PLIKU ZE SKILLAMI!" << std::endl;
    }

}

void wczytaj_imiona (std::vector<std::string> &imiona, const std::string &filename = "../imiona.txt"){
    // Funkcja wczytuje imiona z pliku do wektora stringów - bazy imion.
    std::ifstream plik(filename);
    std::string wers;
    std::cout << "WCZYTYWANIE IMION" << std::endl;
    int liczba_imion = 0;
    if(plik.good()) {
        while (std::getline(plik, wers)) {
            imiona.push_back(wers);
            liczba_imion++;
        }
        std::cout << "WCZYTYWANIE IMION ZAKONCZONE ( " << liczba_imion << " imion )" << std::endl;
    }else{
        std::cout << "!NIE MOZNA OTWORZYC PLIKU Z IMIONAMI!" << std::endl;
    }

}


//////////// FUNKCJE WALKI //////////////
// Funkcje walki generują walki określonych archetypów, pobierając w argumentach indeksy wojowników oraz, za pomocą referencji wektory z wojownikami danych archetypów, skillami odpowiednich archetypów oraz silnik losowości.

void WalkaRR(const int rycerz1, const int rycerz2, std::vector<Rycerz> &rycerze, std::vector<Skill> &skille, std::default_random_engine &silniczek) {
    // Funkcja generująca walkę dwóch rycerzy, usuwająca przegranego i przypisująca zwycięzcy skille przegranego.
    bool koniec = false;
    while(!koniec){
        int wylosowany_cios_1 = rycerze[rycerz1].getCios(silniczek);
        int wylosowany_cios_2 = rycerze[rycerz2].getCios(silniczek);
        int tablica1[9];
        int tablica2[9];
        rycerze[rycerz1].getAtrybuty(tablica1);
        rycerze[rycerz2].getAtrybuty(tablica2);
        std::cout << rycerze[rycerz1].getImie() << " uzywa umiejetnosci " << skille[wylosowany_cios_1].getNazwa() << " - " << skille[wylosowany_cios_1].getOpis() << " Zadane obrazenia: " << skille[wylosowany_cios_1].getDamage(tablica1) << std::endl;

        if(!rycerze[rycerz2].zadajObrazenia(skille[wylosowany_cios_1].getDamage(tablica1))){ //rycerz2 zyje
            std::cout << rycerze[rycerz2].getImie() << " uzywa umiejetnosci " << skille[wylosowany_cios_2].getNazwa() << " - " << skille[wylosowany_cios_2].getOpis() << " Zadane obrazenia: " << skille[wylosowany_cios_2].getDamage(tablica2) << std::endl;
            if(rycerze[rycerz1].zadajObrazenia(skille[rycerze[rycerz2].getCios(silniczek)].getDamage(tablica2))) { //rycerz1 ginie
                rycerze[rycerz2].setCiosy(rycerze[rycerz1].getCiosy());
                std::cout << rycerze[rycerz1].getImie() << " polegl! Zwyciezca jest " << rycerze[rycerz2].getImie()
                          << "!" << std::endl;
                rycerze[rycerz2].resetHP();
                rycerze.erase(rycerze.begin() + rycerz1);
                koniec = true;
            }
        }else if(rycerze[rycerz2].zadajObrazenia(skille[wylosowany_cios_1].getDamage(tablica1))){ //rycerz2 ginie
            rycerze[rycerz1].setCiosy(rycerze[rycerz2].getCiosy());
            std::cout << rycerze[rycerz2].getImie() << " polegl! Zwyciezca jest " << rycerze[rycerz1].getImie() << "!" << std::endl;
            rycerze[rycerz1].resetHP();
            rycerze.erase(rycerze.begin()+rycerz2);
            koniec = true;
        }
    }
}

void WalkaRM(const int rycerz, const int mag, std::vector<Rycerz> &rycerze, std::vector<Mag> &magowie, std::vector<Skill> &v_ciosy, std::vector<Skill> &v_zaklecia, std::default_random_engine &silniczek) {
    // Funkcja generująca walkę rycerza i maga, usuwająca przegranego.
    bool koniec = false;
    while(!koniec){
        int wylosowany_cios_1 = rycerze[rycerz].getCios(silniczek);
        int wylosowany_cios_2 = magowie[mag].getZaklecie(silniczek);
        int tablica1[9];
        int tablica2[9];
        rycerze[rycerz].getAtrybuty(tablica1);
        magowie[mag].getAtrybuty(tablica2);
        std::cout << rycerze[rycerz].getImie() << " uzywa umiejetnosci " << v_ciosy[wylosowany_cios_1].getNazwa() << " - " << v_ciosy[wylosowany_cios_1].getOpis() << " Zadane obrazenia: " << v_ciosy[wylosowany_cios_1].getDamage(tablica1) << std::endl;

        if(!magowie[mag].zadajObrazenia(v_zaklecia[wylosowany_cios_1].getDamage(tablica1))){ //rycerz2 zyje
            std::cout << magowie[mag].getImie() << " uzywa umiejetnosci " << v_zaklecia[wylosowany_cios_2].getNazwa() << " - " << v_zaklecia[wylosowany_cios_2].getOpis() << " Zadane obrazenia: " << v_zaklecia[wylosowany_cios_2].getDamage(tablica2) << std::endl;
            if(rycerze[rycerz].zadajObrazenia(v_zaklecia[magowie[mag].getZaklecie(silniczek)].getDamage(tablica2))) { //rycerz1 ginie
                std::cout << rycerze[rycerz].getImie() << " polegl! Zwyciezca jest " << magowie[mag].getImie()
                          << "!" << std::endl;
                magowie[mag].resetHP();
                rycerze.erase(rycerze.begin() + rycerz);
                koniec = true;
            }
        }else if(magowie[mag].zadajObrazenia(v_ciosy[wylosowany_cios_1].getDamage(tablica1))){ //rycerz2 ginie
            std::cout << magowie[mag].getImie() << " polegl! Zwyciezca jest " << rycerze[rycerz].getImie() << "!" << std::endl;
            rycerze[rycerz].resetHP();
            magowie.erase(magowie.begin()+mag);
            koniec = true;
        }
    }
}

void WalkaPM(const int polimorf, const int mag, std::vector<Polimorf> &polimorfy, std::vector<Mag> &magowie, std::vector<Skill> &v_umiejetnosci, std::vector<Skill> &v_zaklecia, std::default_random_engine &silniczek) {
    // Funkcja generująca walkę polimorfa i maga, usuwająca przegranego.
    bool koniec = false;
    while(!koniec){
        int wylosowany_cios_1 = polimorfy[polimorf].getUmiejetnosc(silniczek);
        int wylosowany_cios_2 = magowie[mag].getZaklecie(silniczek);
        int tablica1[9];
        int tablica2[9];
        polimorfy[polimorf].getAtrybuty(tablica1);
        magowie[mag].getAtrybuty(tablica2);
        std::cout << polimorfy[polimorf].getImie() << " uzywa umiejetnosci " << v_umiejetnosci[wylosowany_cios_1].getNazwa() << " - " << v_umiejetnosci[wylosowany_cios_1].getOpis() << " Zadane obrazenia: " << v_umiejetnosci[wylosowany_cios_1].getDamage(tablica1) << std::endl;

        if(!magowie[mag].zadajObrazenia(v_umiejetnosci[wylosowany_cios_1].getDamage(tablica1))){ //rycerz2 zyje
            std::cout << magowie[mag].getImie() << " uzywa umiejetnosci " << v_zaklecia[wylosowany_cios_2].getNazwa() << " - " << v_zaklecia[wylosowany_cios_2].getOpis() << " Zadane obrazenia: " << v_zaklecia[wylosowany_cios_2].getDamage(tablica2) << std::endl;
            if(polimorfy[polimorf].zadajObrazenia(v_zaklecia[magowie[mag].getZaklecie(silniczek)].getDamage(tablica2))) { //rycerz1 ginie
                std::cout << polimorfy[polimorf].getImie() << " polegl! Zwyciezca jest " << magowie[mag].getImie()
                          << "!" << std::endl;
                magowie[mag].resetHP();
                polimorfy.erase(polimorfy.begin() + polimorf);
                koniec = true;
            }
        }else if(magowie[mag].zadajObrazenia(v_umiejetnosci[wylosowany_cios_1].getDamage(tablica1))){ //rycerz2 ginie
            std::cout << magowie[mag].getImie() << " polegl! Zwyciezca jest " << polimorfy[polimorf].getImie() << "!" << std::endl;
            polimorfy[polimorf].resetHP();
            magowie.erase(magowie.begin()+mag);
            koniec = true;
        }
    }
}

void WalkaPP(const int polimorf1, const int polimorf2, std::vector<Polimorf> &polimorfy, std::vector<Skill> &skille, std::default_random_engine &silniczek) {
    // Funkcja generująca walkę dwóch polimorfy, usuwająca przegranego i przypisująca zwycięzcy skille przegranego.
    bool koniec = false;
    while(!koniec){
        int wylosowany_cios_1 = polimorfy[polimorf1].getUmiejetnosc(silniczek);
        int wylosowany_cios_2 = polimorfy[polimorf2].getUmiejetnosc(silniczek);
        int tablica1[9];
        int tablica2[9];
        polimorfy[polimorf1].getAtrybuty(tablica1);
        polimorfy[polimorf2].getAtrybuty(tablica2);
        std::cout << polimorfy[polimorf1].getImie() << " uzywa umiejetnosci " << skille[wylosowany_cios_1].getNazwa() << " - " << skille[wylosowany_cios_1].getOpis() << " Zadane obrazenia: " << skille[wylosowany_cios_1].getDamage(tablica1) << std::endl;

        if(!polimorfy[polimorf2].zadajObrazenia(skille[wylosowany_cios_1].getDamage(tablica1))){ //polimorf2 zyje
            std::cout << polimorfy[polimorf2].getImie() << " uzywa umiejetnosci " << skille[wylosowany_cios_2].getNazwa() << " - " << skille[wylosowany_cios_2].getOpis() << " Zadane obrazenia: " << skille[wylosowany_cios_2].getDamage(tablica2) << std::endl;
            if(polimorfy[polimorf1].zadajObrazenia(skille[polimorfy[polimorf2].getUmiejetnosc(silniczek)].getDamage(tablica2))) { //polimorf1 ginie
                polimorfy[polimorf2].setUmiejetnosci(polimorfy[polimorf1].getUmiejetnosci());
                std::cout << polimorfy[polimorf1].getImie() << " polegl! Zwyciezca jest " << polimorfy[polimorf2].getImie()
                          << "!" << std::endl;
                polimorfy[polimorf2].resetHP();
                polimorfy.erase(polimorfy.begin() + polimorf1);
                koniec = true;
            }
        }else if(polimorfy[polimorf2].zadajObrazenia(skille[wylosowany_cios_1].getDamage(tablica1))){ //polimorf2 ginie
            polimorfy[polimorf1].setUmiejetnosci(polimorfy[polimorf2].getUmiejetnosci());
            std::cout << polimorfy[polimorf2].getImie() << " polegl! Zwyciezca jest " << polimorfy[polimorf1].getImie() << "!" << std::endl;
            polimorfy[polimorf1].resetHP();
            polimorfy.erase(polimorfy.begin()+polimorf2);
            koniec = true;
        }
    }
}

void WalkaMM(const int mag1, const int mag2, std::vector<Mag> &magowie, std::vector<Skill> &skille, std::default_random_engine &silniczek) {
    // Funkcja generująca walkę dwóch magów, usuwająca przegranego i przypisująca zwycięzcy skille przegranego.
    bool koniec = false;
    while(!koniec){
        int wylosowany_cios_1 = magowie[mag1].getZaklecie(silniczek);
        int wylosowany_cios_2 = magowie[mag2].getZaklecie(silniczek);
        int tablica1[9];
        int tablica2[9];
        magowie[mag1].getAtrybuty(tablica1);
        magowie[mag2].getAtrybuty(tablica2);
        std::cout << magowie[mag1].getImie() << " uzywa umiejetnosci " << skille[wylosowany_cios_1].getNazwa() << " - " << skille[wylosowany_cios_1].getOpis() << " Zadane obrazenia: " << skille[wylosowany_cios_1].getDamage(tablica1) << std::endl;

        if(!magowie[mag2].zadajObrazenia(skille[wylosowany_cios_1].getDamage(tablica1))){ //mag2 zyje
            std::cout << magowie[mag2].getImie() << " uzywa umiejetnosci " << skille[wylosowany_cios_2].getNazwa() << " - " << skille[wylosowany_cios_2].getOpis() << " Zadane obrazenia: " << skille[wylosowany_cios_2].getDamage(tablica2) << std::endl;
            if(magowie[mag1].zadajObrazenia(skille[magowie[mag2].getZaklecie(silniczek)].getDamage(tablica2))) { //mag1 ginie
                magowie[mag2].setZaklecia(magowie[mag1].getZaklecia());
                std::cout << magowie[mag1].getImie() << " polegl! Zwyciezca jest " << magowie[mag2].getImie()
                          << "!" << std::endl;
                magowie[mag2].resetHP();
                magowie.erase(magowie.begin() + mag1);
                koniec = true;
            }
        }else if(magowie[mag2].zadajObrazenia(skille[wylosowany_cios_1].getDamage(tablica1))){ //mag2 ginie
            magowie[mag1].setZaklecia(magowie[mag2].getZaklecia());
            std::cout << magowie[mag2].getImie() << " polegl! Zwyciezca jest " << magowie[mag1].getImie() << "!" << std::endl;
            magowie[mag1].resetHP();
            magowie.erase(magowie.begin()+mag2);
            koniec = true;
        }
    }
}

void WalkaPR(const int polimorf, const int rycerz, std::vector<Polimorf> &polimorfy, std::vector<Rycerz> &rycerze, std::vector<Skill> &v_umiejetnosci, std::vector<Skill> &v_ciosy, std::default_random_engine &silniczek) {
    // Funkcja generująca walkę polimorfa i rycerza, usuwająca przegranego.
    bool koniec = false;
    while(!koniec){
        int wylosowany_cios_1 = polimorfy[polimorf].getUmiejetnosc(silniczek);
        int wylosowany_cios_2 = rycerze[rycerz].getCios(silniczek);
        int tablica1[9];
        int tablica2[9];
        polimorfy[polimorf].getAtrybuty(tablica1);
        rycerze[rycerz].getAtrybuty(tablica2);
        std::cout << polimorfy[polimorf].getImie() << " uzywa umiejetnosci " << v_umiejetnosci[wylosowany_cios_1].getNazwa() << " - " << v_umiejetnosci[wylosowany_cios_1].getOpis() << " Zadane obrazenia: " << v_umiejetnosci[wylosowany_cios_1].getDamage(tablica1) << std::endl;

        if(!rycerze[rycerz].zadajObrazenia(v_umiejetnosci[wylosowany_cios_1].getDamage(tablica1))){ //rycerz2 zyje
            std::cout << rycerze[rycerz].getImie() << " uzywa umiejetnosci " << v_ciosy[wylosowany_cios_2].getNazwa() << " - " << v_ciosy[wylosowany_cios_2].getOpis() << " Zadane obrazenia: " << v_ciosy[wylosowany_cios_2].getDamage(tablica2) << std::endl;
            if(polimorfy[polimorf].zadajObrazenia(v_ciosy[rycerze[rycerz].getCios(silniczek)].getDamage(tablica2))) { //rycerz1 ginie
                std::cout << polimorfy[polimorf].getImie() << " polegl! Zwyciezca jest " << rycerze[rycerz].getImie()
                          << "!" << std::endl;
                rycerze[rycerz].resetHP();
                polimorfy.erase(polimorfy.begin() + polimorf);
                koniec = true;
            }
        }else if(rycerze[rycerz].zadajObrazenia(v_umiejetnosci[wylosowany_cios_1].getDamage(tablica1))){ //rycerz2 ginie
            std::cout << rycerze[rycerz].getImie() << " polegl! Zwyciezca jest " << polimorfy[polimorf].getImie() << "!" << std::endl;
            polimorfy[polimorf].resetHP();
            rycerze.erase(rycerze.begin()+rycerz);
            koniec = true;
        }
    }
}

int main() {
    /* 1) Program symuluje, przez opis słowny, walki wojowników.
     * Można stworzyć do 10 wojowników. Wojownicy mogą być trzech typów: rycerz, mag i polimorf.
     * Wszyscy wojownicy mają kilka cech i umiejętności wspólnych jak ‘poziom życia’ czy ‘atak’
     * oraz cechy przynależne tylko i wyłącznie do danego typu.
     * Przed walką cechy przeciwników ustawiane są losowo.
     * Gdy dochodzi do walki wyliczana jest moc ‘ataku’ każdego z przeciwników na podstawie wartości wszystkich jego cech.
     * Wygrywa ten wojownik, który ma większą moc ataku.
     * Zwycięzca przejmuje wszystkie cechy przegranego, których do tej pory nie posiadał.
     * Przegrany jest unicestwiany. Walki toczą się do momentu gdy pozostaje tylko jeden wojownik. */

    std::vector<Polimorf> polimorfy;
    std::vector<Mag> magowie;
    std::vector<Rycerz> rycerze;
    std::vector<Skill> v_ciosy;
    std::vector<Skill> v_zaklecia;
    std::vector<Skill> v_umiejetnosci;
    std::vector<std::string> imiona;

    wczytaj_skille(v_ciosy, v_zaklecia, v_umiejetnosci);
    wczytaj_imiona(imiona);

    unsigned ziarno = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine silnik_losowosci(ziarno); //arg dla random device: ziarno()
    std::uniform_int_distribution<int> przedzial99(0, 99);
    std::uniform_int_distribution<int> przedzial20(1, 20);
    std::uniform_int_distribution<int> przedzial10(1, 10);
    std::uniform_int_distribution<int> przedzialR(1, 8);

    int l_r = przedzialR(silnik_losowosci);
    std::uniform_int_distribution<int> przedzialM(1, 9-l_r);
    int l_m = 10 - l_r - przedzialM(silnik_losowosci);
    int l_p = 10 - l_r - l_m;

    std::cout << "W turnieju bierze udzial: " << l_r << " rycerzy, " << l_m << " magow, " << l_p << " polimorfow." << std::endl;

    for(int i=0; i<l_r; i++) {
        rycerze.emplace_back(Rycerz(imiona[przedzial99(silnik_losowosci)], silnik_losowosci, przedzial20, przedzial10));
        rycerze[i].print();
    }
    for(int j=0; j<l_m; j++) {
        magowie.emplace_back(Mag(imiona[przedzial99(silnik_losowosci)], silnik_losowosci, przedzial20, przedzial10));
        magowie[j].print();
    }
    for(int k=0; k<l_p; k++) {
        polimorfy.emplace_back(Polimorf(imiona[przedzial99(silnik_losowosci)], silnik_losowosci, przedzial20, przedzial10));
        polimorfy[k].print();
    }

    /*
    Przykładowe wywołania funkcji walki:
    WalkaRR (0,1,rycerze,v_ciosy,silnik_losowosci);
    WalkaRM (0,1,rycerze,magowie,v_ciosy,v_zaklecia,silnik_losowosci);
    WalkaPM (0,1,polimorfy,magowie,v_umiejetnosci,v_zaklecia,silnik_losowosci);
    WalkaPP (0,1,polimorfy,v_umiejetnosci,silnik_losowosci);
    WalkaMM (0,1,magowie,v_zaklecia,silnik_losowosci);
    WalkaPR (0,1,polimorfy,rycerze,v_umiejetnosci,v_ciosy,silnik_losowosci);
    */

    int nr_walki = 1;
    while(rycerze.size() > 1){
        int wojak1 = przedzial10(silnik_losowosci) % rycerze.size();
        int wojak2 = przedzial10(silnik_losowosci) % rycerze.size();
        while(wojak2 == wojak1){
            wojak2 = przedzial10(silnik_losowosci) % rycerze.size();
        }
        std::cout << "------- WALKA NR " << nr_walki << "---------" << std::endl;
        nr_walki++;
        WalkaRR(wojak1, wojak2, rycerze, v_ciosy, silnik_losowosci);
    }
    while(magowie.size() > 1){
        int wojak1 = przedzial10(silnik_losowosci) % magowie.size();
        int wojak2 = przedzial10(silnik_losowosci) % magowie.size();
        while(wojak2 == wojak1){
            wojak2 = przedzial10(silnik_losowosci) % magowie.size();
        }
        std::cout << "------- WALKA NR " << nr_walki << "---------" << std::endl;
        nr_walki++;
        WalkaMM(wojak1, wojak2, magowie, v_zaklecia, silnik_losowosci);
    }
    while(polimorfy.size() > 1){
        int wojak1 = przedzial10(silnik_losowosci) % polimorfy.size();
        int wojak2 = przedzial10(silnik_losowosci) % polimorfy.size();
        while(wojak2 == wojak1){
            wojak2 = przedzial10(silnik_losowosci) % polimorfy.size();
        }
        std::cout << "------- WALKA NR " << nr_walki << "---------" << std::endl;
        nr_walki++;
        WalkaPP(wojak1, wojak2, polimorfy, v_umiejetnosci, silnik_losowosci);
    }
    while(!rycerze.empty() && !magowie.empty()){
        int wojak1 = przedzial10(silnik_losowosci) % rycerze.size();
        int wojak2 = przedzial10(silnik_losowosci) % magowie.size();
        std::cout << "------- WALKA NR " << nr_walki << "---------" << std::endl;
        nr_walki++;
        WalkaRM(wojak1, wojak2, rycerze, magowie, v_ciosy, v_zaklecia, silnik_losowosci);
    }
    while(!polimorfy.empty() && !magowie.empty()){
        int wojak1 = przedzial10(silnik_losowosci) % polimorfy.size();
        int wojak2 = przedzial10(silnik_losowosci) % magowie.size();
        std::cout << "------- WALKA NR " << nr_walki << "---------" << std::endl;
        nr_walki++;
        WalkaPM(wojak1, wojak2, polimorfy, magowie, v_umiejetnosci, v_zaklecia, silnik_losowosci);
    }
    while(!rycerze.empty() && !polimorfy.empty()){
        int wojak1 = przedzial10(silnik_losowosci) % rycerze.size();
        int wojak2 = przedzial10(silnik_losowosci) % polimorfy.size();
        std::cout << "------- WALKA NR " << nr_walki << "---------" << std::endl;
        nr_walki++;
        WalkaPR(wojak1, wojak2, polimorfy, rycerze, v_umiejetnosci, v_ciosy, silnik_losowosci);
    }

    std::cout << "------------------------------------------------" << std::endl;
    if(!rycerze.empty())
        std::cout << "Zwyciezca turnieju jest: " << rycerze[0].getImie() << " !!!" << std::endl;
    else if(!magowie.empty())
        std::cout << "Zwyciezca turnieju jest: " << magowie[0].getImie() << " !!!" << std::endl;
    else if(!polimorfy.empty())
        std::cout << "Zwyciezca turnieju jest: " << polimorfy[0].getImie() << " !!!" << std::endl;


    std::cout << "KONIEC" << std::endl;
    return 0;
}
