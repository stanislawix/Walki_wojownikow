#ifndef HK1_SKILL_H
#define HK1_SKILL_H
#include <string>
#include <iostream>

class Skill {
private:
    std::string nazwa;
    std::string opis;
    char archetyp;
    double wagi_atrubutow[9];

public:
    Skill(std::string &nazwa, std::string &opis, char &archetyp, double* wagi);
    ~Skill() = default;

    std::string getNazwa();
    std::string getOpis();
    char getArchetyp() const;
    double* getWagi();
    int getDamage(int* atrybuty);

    void setNazwa(std::string &nazwa);
    void setOpis(std::string &opis);
    void setArchetyp(char &archetyp);
    void setWagi(double* wagi);
    void print();
};




#endif //HK1_SKILL_H
