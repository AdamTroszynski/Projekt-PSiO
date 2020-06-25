#ifndef INFORMACJE_H
#define INFORMACJE_H
#include <sstream>
class Informacje
{
public:
    Informacje()
    {
        wynik = 0;
        funkcja = MENU;
    };
    int wynik;
    enum PossibleGameStates { GRA, MENU, WYNIK, KONIEC,POMOC };
    PossibleGameStates funkcja;

    static std::string zmianaintnastr(int liczba)
    {
        std::ostringstream zmianainnast;
        zmianainnast << liczba;
        std::string tekst = zmianainnast.str();
        return tekst;
    };
    static const int WielkoscCzesci = 5;//wielkośćczęściwężaorazszybkość
    static const int WysokoscOkna = 600;//wysokość okna
    static const int SzerokoscOkna = 800;//szerokość okna
    static constexpr const char* NazwaGry = "Snake";
    static const int Kolor_weza_R = 255;
    static const int Kolor_weza_G = 255;
    static const int Kolor_weza_B = 255;
    static const int Kolor_pocisku_R = 255;
    static const int Kolor_pocisku_G = 255;
    static const int Kolor_pocisku_B = 0;
    static constexpr float czasgenjablka = 3.0;
    static constexpr float czaspocisku = 5;
    static int generator(int od, int doo)
        {
            return rand()%(doo-od+1)+od;
        };

};

#endif // INFORMACJE_H
