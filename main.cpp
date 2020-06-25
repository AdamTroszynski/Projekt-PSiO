#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <Okna.h>
#include <informacje.h>
#include <dzwiek.h>
#include <Kolizja.h>
class CzescW : public Przeszkoda
{
public:
    enum Kierunki{ GORA, DOL, LEWO = 3, PRAWO};
    Kierunki ruchpoczatkowy;

    CzescW()
    {
        rec.setFillColor(sf::Color(Informacje::Kolor_weza_R, Informacje::Kolor_weza_G, Informacje::Kolor_weza_B));
        rec.setSize(sf::Vector2f(Informacje::WielkoscCzesci,Informacje::WielkoscCzesci));
        ruchpoczatkowy = LEWO;
    };
};
class Waz : public sf::Sprite
{
public:
    int dlugosc;
    Waz()
    {
        dlugosc = 0;
        dlugoscwaz(3);
    };
    virtual void draw(sf::RenderTarget& cel, sf::RenderStates) const
    {
        for(size_t i=0; i<czesci.size(); i++)
        {
            cel.draw(czesci[i].rec);

        }
    };
    void dlugoscwaz(int pluslubminus)
    {
        dlugosc += pluslubminus;

        if(pluslubminus > 0){
            for(int i=0; i<pluslubminus; i++)
            {
               czesci.push_back(CzescW());

                if(czesci.size() > 1){
                    czesci[czesci.size()-1].rec.setPosition(wspolrzednenowejczesci());
                    czesci[czesci.size()-1].ruchpoczatkowy = czesci[czesci.size()-2].ruchpoczatkowy;
                }
                else {
                    czesci[czesci.size()-1].rec.setPosition(nasrodku());
                }
            }}
        else if(pluslubminus < 0){
            for(int i=0; i<(pluslubminus-1); i++)
            {
                if(czesci.size() > 0) czesci.pop_back();
            }
        }
    };
    std::vector <CzescW> czesci;

    void refreschwspolzedne()
    {
        for(size_t i=0; i<czesci.size(); i++)
        {
            if(czesci[i].ruchpoczatkowy == CzescW::LEWO){czesci[i].rec.move(-Informacje::WielkoscCzesci,0);};
            if(czesci[i].ruchpoczatkowy == CzescW::PRAWO){czesci[i].rec.move(Informacje::WielkoscCzesci,0);};
            if(czesci[i].ruchpoczatkowy == CzescW::GORA){czesci[i].rec.move(0,-Informacje::WielkoscCzesci);};
            if(czesci[i].ruchpoczatkowy == CzescW::DOL){czesci[i].rec.move(0,Informacje::WielkoscCzesci);};
        }
    };
    void refreshczesci()
    {
        for(size_t i=czesci.size()-1; i>0; i--)
        {
            czesci[i].ruchpoczatkowy = czesci[i-1].ruchpoczatkowy;
        }
    };
    bool kanibalizm()
    {
        for(size_t i=1; i<czesci.size(); i++)
        {
            if(kolizja.JestKolizja(czesci[0], czesci[i])){
                return true;
            }
        }

        return false;
    };

    void obrot(CzescW::Kierunki kierunek)
        {
            if(cobrot(kierunek) && czesci.size() > 0) czesci[0].ruchpoczatkowy = kierunek;
        };



    bool pozaekran()
    {
        if(czesci.size() > 0){
            sf::RectangleShape *koniec = &czesci[0].rec;

            if(koniec->getPosition().x > Informacje::SzerokoscOkna || koniec->getPosition().x < 0){
                return true;
            }
            else if(koniec->getPosition().y > Informacje::WysokoscOkna || koniec->getPosition().y < 0){
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    };



    Kolizja kolizja;
    bool cobrot(CzescW::Kierunki kierunek)
    {
        if(czesci.size() > 0){
            if(abs(kierunek - czesci[0].ruchpoczatkowy) >= 2) return true;
            else return false;
        }
        else {
            return false;
        }
    };
    void usuwanieczesci(int liczbac)
    {
        for(int i=0; i<(liczbac*-1); i++)
        {
            if(czesci.size() > 0) czesci.pop_back();
        }
    };
    sf::Vector2f nasrodku()
    {
        sf::Vector2f wektor;
        wektor.x = Informacje::SzerokoscOkna/2 - Informacje::WielkoscCzesci/2;
        wektor.y = Informacje::WysokoscOkna/2 - Informacje::WielkoscCzesci/2;
        return wektor;
    };
    sf::Vector2f wspolrzednenowejczesci()
    {
        sf::Vector2f wektor;
        CzescW *wczesniejszacz = &czesci[czesci.size()-2];

        if(wczesniejszacz->ruchpoczatkowy == CzescW::GORA){
            wektor.x = wczesniejszacz->rec.getPosition().x;
            wektor.y = wczesniejszacz->rec.getPosition().y + Informacje::WielkoscCzesci;
        }
        if(wczesniejszacz->ruchpoczatkowy == CzescW::DOL){
            wektor.x = wczesniejszacz->rec.getPosition().x;
            wektor.y = wczesniejszacz->rec.getPosition().y - Informacje::WielkoscCzesci;
        }
        if(wczesniejszacz->ruchpoczatkowy == CzescW::LEWO){
            wektor.x = wczesniejszacz->rec.getPosition().x + Informacje::WielkoscCzesci;
            wektor.y = wczesniejszacz->rec.getPosition().y;
        }
        if(wczesniejszacz->ruchpoczatkowy == CzescW::PRAWO){
            wektor.x = wczesniejszacz->rec.getPosition().x - Informacje::WielkoscCzesci;
            wektor.y = wczesniejszacz->rec.getPosition().y;
        }
        return wektor;
    };

};
class Jablko : public Przeszkoda, public sf::Sprite
{
public:
    int zmianadlugosci;
    enum Rodzaj {DOBRE, ZEPSUTE};
    Rodzaj rodzaj;
    Jablko()
    {
        rodzaj = Rodzaj(losujrodzaj());
        zmianadlugosci = losujrozmiar();
        rec.setPosition(losujwspolzedne());
    };
    virtual void draw(sf::RenderTarget& cel,sf::RenderStates) const
        {
            cel.draw(rec);

        };
//sf::Texture teksturaj;
    int losujrodzaj()
    {
        int los = Informacje::generator(0,20);
        if(los > 3){
            return 0;
        }
        else {
            return 1;
        }
    };
    int losujrozmiar()
    {
        int losujrozmiar = Informacje::generator(10,20);
        rec.setSize(sf::Vector2f(losujrozmiar,losujrozmiar));

        if(rodzaj == Rodzaj::ZEPSUTE){
            //rec.setTexture(&teksturaj);
            rec.setFillColor(sf::Color(150,0,0));

            return -losujrozmiar;
        }
        else {

            //rec.setTexture(&teksturaj);
            rec.setFillColor(sf::Color(0,255,0));

            return losujrozmiar;
        }
    };
    sf::Vector2f losujwspolzedne()
    {
        sf::Vector2f miejsce;

        miejsce.x = Informacje::generator(0,Informacje::SzerokoscOkna-zmianadlugosci);
        miejsce.y = Informacje::generator(0,Informacje::WysokoscOkna-zmianadlugosci);

        return miejsce;
    };
};
class Pocisk : public Przeszkoda
{
public:
    enum Pozycja { GORA, DOL, LEWO, PRAWO };
    Pozycja pozycja;
    bool porusza;
    bool uszkodzenie;
    Pocisk()
    {
        rec.setFillColor(sf::Color(Informacje::Kolor_pocisku_R,Informacje::Kolor_pocisku_G,Informacje::Kolor_pocisku_B));

        porusza = false;
        uszkodzenie = true;
    };
    void pozycjapocisku()
    {
        pozycja = Pozycja(Informacje::generator(0,3));
        int losuj = Informacje::generator(50,Informacje::WysokoscOkna-50);
        if(pozycja == GORA){rec.setPosition(losuj,Informacje::WysokoscOkna+5);rec.setSize(sf::Vector2f(10,150));}
        if(pozycja == DOL){rec.setPosition(losuj,-205);rec.setSize(sf::Vector2f(10,200));}
        if(pozycja == LEWO){rec.setPosition(Informacje::SzerokoscOkna+205,losuj);rec.setSize(sf::Vector2f(150,10));}
        if(pozycja == PRAWO){rec.setPosition(-205,losuj);rec.setSize(sf::Vector2f(200,10));}
    }
    bool pozaekran()
    {
        if(pozycja == GORA){if(rec.getPosition().y + rec.getGlobalBounds().height < 0) return true;}
        else if(pozycja == DOL){if(rec.getPosition().y - rec.getGlobalBounds().height > Informacje::WysokoscOkna) return true;}
        else if(pozycja == LEWO){if(rec.getPosition().x + rec.getGlobalBounds().width < 0) return true;}
        else if(pozycja == PRAWO){if(rec.getPosition().x - rec.getGlobalBounds().width > Informacje::SzerokoscOkna) return true;}
        else {return false;}
        return false;
    };
    void refreshpozycjapocisku()
    {
        if(porusza){
            if(pozycja == GORA){rec.move(0,-10);}
            if(pozycja == DOL){rec.move(0,10);}
            if(pozycja == LEWO){rec.move(-10,0);}
            if(pozycja == PRAWO){rec.move(10,0);}
        }
    };
    void restart()
    {
        rec.setFillColor(sf::Color(Informacje::Kolor_pocisku_R,Informacje::Kolor_pocisku_G,Informacje::Kolor_pocisku_B));
        uszkodzenie = true;
    };
    void dezintegracja()
    {
        rec.setFillColor(sf::Color(Informacje::Kolor_pocisku_R*0,Informacje::Kolor_pocisku_G*0,Informacje::Kolor_pocisku_B*0));
        uszkodzenie = false;
    };


};
class Gra
{
public:
    Gra(sf::RenderWindow &window, Informacje &informacje, sf::Font czcionka, sf::Texture tekstura)
    {
        this->tekstura = tekstura;
        this->czcionka = czcionka;
        this->informacje = &informacje;
        this->window = &window;
        czylaser = false;
    };
    void start()
    {
        while(informacje->funkcja == Informacje::GRA)
        {
            sf::Event event;
            while(window->pollEvent(event))
            {
                if(event.type == sf::Event::Closed){
                    informacje->funkcja = Informacje::KONIEC;
                }

                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Escape){informacje->funkcja = Informacje::MENU;}
                    if(event.key.code == sf::Keyboard::W){waz.obrot(CzescW::GORA);}
                    if(event.key.code == sf::Keyboard::S){waz.obrot(CzescW::DOL);}
                    if(event.key.code == sf::Keyboard::A){waz.obrot(CzescW::LEWO);}
                    if(event.key.code == sf::Keyboard::D){waz.obrot(CzescW::PRAWO);}
                }
            }

            refresh();
            stanjablka();
            refreshpocisk();

            sf::Vector2f mouse(sf::Mouse::getPosition(*window));
            if(pocisk.rec.getGlobalBounds().contains(mouse)){
                pocisk.dezintegracja();
            }

            if(koniecgry()){
                informacje->funkcja = Informacje::WYNIK;
            }

            informacje->wynik = zmieniajwynik();
            window->clear(sf::Color::White);
            sf::Sprite sprite_grass;
            sprite_grass.setTexture(tekstura);
            tekstura.setRepeated(true);
            sprite_grass.setTextureRect(sf::IntRect(0, 0, 800, 600));
            window->draw(sprite_grass);
            window->draw(waz);
            window->draw(pocisk.rec);
            rysjablka();
            window->display();

        }
    };


    void rysjablka(){
        for(size_t i=0; i<jablka.size(); i++)
        {
            window->draw(jablka[i]);
        }


    };
bool koniecgry()
    {
        if(waz.kanibalizm() || waz.pozaekran() || waz.dlugosc <= 0){
            return true;
        }
        else {
            return false;
        }
    };
int zmieniajwynik()
    {
        return waz.dlugosc * 3;
    };

void stanjablka()
    {
        if(genjablka()) genejablka();
        zjedzone();
    };
void genejablka()
    {
        if(jablka.size() == 10) jablka.erase(jablka.begin());
        if(jablka.size() < 10) jablka.push_back(Jablko());
    };
void zjedzone()
    {
        for(size_t i=0; i<jablka.size(); i++)
        {
            if(kolizja.JestKolizja(waz.czesci[0],jablka[i])){
                if(jablka[i].zmianadlugosci + waz.dlugosc > 0){
                    waz.dlugoscwaz(jablka[i].zmianadlugosci);
                }
                else {
                    waz.dlugoscwaz(waz.dlugosc * -1);
                }

                jablka.erase(jablka.begin() + i);
            }
        }
    };
void obciecie()
    {
        if(pocisk.uszkodzenie){
            for(size_t i=0; i<waz.czesci.size(); i++)
            {
                if(kolizja.JestKolizja(pocisk, waz.czesci[i])){
                    waz.dlugoscwaz(-1 * (waz.czesci.size()-i-1));
                }
            }
        }
    };
private:
sf::Clock Rclock;
sf::Time Rela;
sf::Time RTR;
void refresh()
    {
        Rela =Rclock.getElapsedTime();
        RTR = sf::milliseconds(10);

        if(Rela > RTR){
            Rclock.restart();
            waz.refreschwspolzedne();
            waz.refreshczesci();
            pocisk.refreshpozycjapocisku();
        }
    };
sf::Clock Jclock;
sf::Time Jela;
sf::Time JTR;
bool genjablka()
{
    JTR = sf::seconds(Informacje::czasgenjablka);
    Jela = Jclock.getElapsedTime();

    if(Jela > JTR){
        Jclock.restart();
        return true;
    }
    return 0;
};
sf::Clock Pclock;
sf::Time Pela;
sf::Time PTR;
bool czylaser;
void refreshpocisk()
    {
        if(czylaser == false){
            pocisk.pozycjapocisku();

            pocisk.restart();
            czylaser = true;
        }

        if(strzal()){
            pocisk.porusza = true;
            dzwieki.odtworz(Dzwiek::POCISK);
        }

        if(pocisk.porusza){
            obciecie();
            if(pocisk.pozaekran()){
                pocisk.porusza = false;
                czylaser = false;
            }
        }
    };
bool strzal()
    {
        PTR = sf::seconds(Informacje::czaspocisku);
        Pela = Pclock.getElapsedTime();

        if(Pela > PTR){
            Pclock.restart();
            return true;
        }
        else {
            return false;
        }
    };
    sf::RenderWindow *window;
    sf::Texture tekstura;
    sf::Font czcionka;
    Informacje *informacje;
    Waz waz;
    CzescW czesc;
    Jablko jablko;
    Pocisk pocisk;
    Kolizja kolizja;
    Dzwiek dzwieki;
    std::vector <Jablko> jablka;

};
class Inicjalizacja
{
public:
    Inicjalizacja()
    {
        window.create(sf::VideoMode(Informacje::SzerokoscOkna,Informacje::WysokoscOkna),Informacje::NazwaGry);
        tekstura1.loadFromFile("Texture/teksturamenu.jpg");
        tekstura2.loadFromFile("Texture/trawa.jpg");
        czcionka.loadFromFile("Baza/Bleeding_Cowboys.ttf");

        srand(time(NULL));
    };
void start(){
        while(window.isOpen())
        {
            if(informacje.funkcja == Informacje::MENU)
            {
                oknomenu Menu(window, informacje, czcionka, tekstura1);
                dzwiek.odtworz(Dzwiek::OKNA);
                Menu.pokaz();
            }
            if(informacje.funkcja == Informacje::POMOC)
            {
                oknopomocy pomoc(window, informacje , czcionka, tekstura1);
                dzwiek.odtworz(Dzwiek::OKNA);
                pomoc.pokaz();
            }
            if(informacje.funkcja == Informacje::GRA)
            {
                Gra gra(window, informacje, czcionka, tekstura2);
                dzwiek.odtworz(Dzwiek::GRA);
                gra.start();
            }

            if(informacje.funkcja == Informacje::WYNIK)
            {
                oknowyniku wynik(window, informacje, czcionka, tekstura1);
                dzwiek.odtworz(Dzwiek::OKNA);
                wynik.pokaz();
            }

            if(informacje.funkcja == Informacje::KONIEC){window.close();}

        }
    };
private:
sf::RenderWindow window;
Informacje informacje;
sf::Font czcionka;
sf::Texture tekstura1;
sf::Texture tekstura2;
Dzwiek dzwiek;
CzescW czesc;

};

int main()
{
   Inicjalizacja uruchom;
   uruchom.start();
   return 0;
}
