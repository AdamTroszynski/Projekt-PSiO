#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
class Informacje
{
public:
    Informacje()
    {
        wynik = 0;
        funkcja = MENU;
    };
    int wynik;
    enum PossibleGameStates { GRA, MENU, WYNIK, KONIEC };
    PossibleGameStates funkcja;

    static std::string convertIntToString(int liczba)
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

    static int generator(int from, int to)
        {
            return rand()%(to-from+1)+from;
        };

};
class Przeszkoda
{
public:
    sf::RectangleShape rec;
    sf::Vector2f getPosition(){return rec.getPosition();}
    sf::Vector2f getSize(){return rec.getSize();};
    void setTexture(sf::Texture tekstura){rec.setTexture(&tekstura);}
};
class Kolizja
{
public:
    bool JestKolizja(Przeszkoda &p1, Przeszkoda &p2)
    {
        refreshWspolzedne(p1,p2);
        if(ywspolzednep1+wysokoscp1 > ywspolzednep2 && xwspolzednep1 < xwspolzednep2+szerokoscp2 && ywspolzednep1 < ywspolzednep2+wysokoscp2 && xwspolzednep1+szerokoscp1 > xwspolzednep2 ){
            return true;
        }
        else {
            return false;
        }
    };
private:
    float xwspolzednep1;
    float ywspolzednep1;
    float xwspolzednep2;
    float ywspolzednep2;
    float szerokoscp1;
    float wysokoscp1;
    float szerokoscp2;
    float wysokoscp2;

    void refreshWspolzedne(Przeszkoda &p1, Przeszkoda &p2)
        {
            szerokoscp1 = p1.getSize().x;
            wysokoscp1 = p1.getSize().y;
            szerokoscp2 = p2.getSize().x;
            wysokoscp2 = p2.getSize().y;
            xwspolzednep1 = p1.getPosition().x;
            ywspolzednep1 = p1.getPosition().y;
            xwspolzednep2 = p2.getPosition().x;
            ywspolzednep2 = p2.getPosition().y;

        };
};
class CzescW : public Przeszkoda
{
public:
    enum Kierunki{ GORA, DOL, LEWO = 3, PRAWO = 4 };
    Kierunki ruchpoczatkowy;

    CzescW()
    {
        rec.setFillColor(sf::Color::Green);
        rec.setTexture(&tekstura);
        rec.setSize(sf::Vector2f(Informacje::WielkoscCzesci,Informacje::WielkoscCzesci));
        ruchpoczatkowy = LEWO;
    };
    void ustawTekstura(sf::Texture tekstura)
    {
        this->tekstura = tekstura;
    };
private:
    sf::Texture tekstura;
};
class Waz : public sf::Sprite
{
public:
    int dlugosc;
    Waz()
    {
        dlugosc = 0;
        rozmiarwaz(1);
    };
    virtual void draw(sf::RenderTarget& cel, sf::RenderStates) const
    {
        for(size_t i=0; i<czesci.size(); i++)
        {
            cel.draw(czesci[i].rec);
        }
    };
    void rozmiarwaz(int pluslubminus)
    {
        dlugosc += pluslubminus;

        if(pluslubminus > 0) dodawanieczesci(pluslubminus);
        else if(pluslubminus < 0) usuwanieczesci(pluslubminus);
    };
    std::vector <CzescW> czesci;

    void refreschwspolzedne()
    {
        for(size_t i=0; i<czesci.size(); i++)
        {
            switch(czesci[i].ruchpoczatkowy)
            {
                case CzescW::LEWO: czesci[i].rec.move(-Informacje::WielkoscCzesci,0); break;
                case CzescW::PRAWO: czesci[i].rec.move(Informacje::WielkoscCzesci,0); break;
                case CzescW::GORA: czesci[i].rec.move(0,-Informacje::WielkoscCzesci); break;
                case CzescW::DOL: czesci[i].rec.move(0,Informacje::WielkoscCzesci); break;

            }
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

private:

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
    void dodawanieczesci(int liczbac)
    {
        for(int i=0; i<liczbac; i++)
        {
           czesci.push_back(CzescW());

            if(czesci.size() > 1){
                czesci[czesci.size()-1].rec.setPosition(wspolrzednenowejczesci());
                czesci[czesci.size()-1].ruchpoczatkowy = czesci[czesci.size()-2].ruchpoczatkowy;
            }
            else {
                czesci[czesci.size()-1].rec.setPosition(nasrodku());
            }
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
class Dzwiek
{
public:
    sf::SoundBuffer sB1dzwiek;
    sf::SoundBuffer sB2dzwiek;
    sf::SoundBuffer sB3dzwiek;

    sf::Sound s1dzwiek;
    sf::Sound s2dzwiek;

    sf::Music m1dzwiek;
    sf::Music m2dzwiek;

    enum Dzwieki { WOLNO, SZYBKO, POCISK, MUS1, MUS2 };

    Dzwiek()
    {
        sB1dzwiek.loadFromFile("data/slowDown");
        sB2dzwiek.loadFromFile("data/speedUp");
        sB3dzwiek.loadFromFile("data/laserShot");
        m1dzwiek.openFromFile("data/Ending.wav");
        m2dzwiek.openFromFile("data/TitleScreen.wav");

        m1dzwiek.setLoop(true);
        m2dzwiek.setLoop(true);
    };
    void play(Dzwieki muzyka)
    {
        if(muzyka == SZYBKO){
            s1dzwiek.setBuffer(sB2dzwiek);
            s1dzwiek.play();
        }
        if(muzyka == WOLNO){
            s1dzwiek.setBuffer(sB1dzwiek);
            s1dzwiek.play();
        }
        if(muzyka == POCISK){
            s2dzwiek.setBuffer(sB3dzwiek);
            s2dzwiek.play();
        }
        if(muzyka == MUS1){
            if(m1dzwiek.getStatus() == sf::SoundSource::Status::Stopped){
                m1dzwiek.play();
            }
            if(m2dzwiek.getStatus() == sf::SoundSource::Status::Playing){
                m2dzwiek.stop();
            }
        }
        if(muzyka == MUS2){
            m1dzwiek.stop();
            m2dzwiek.play();
        }
    };
};
class Jablko : public Przeszkoda, public sf::Sprite
{
public:
    int zmianadlugosci;
    enum Rodzaj { DOBRE, ZEPSUTE };
    Rodzaj rodzaj;
    Jablko()
    {
        rodzaj = Rodzaj(losujrodzaj());
        zmianadlugosci = losujrozmiar();
        rec.setPosition(losujwspolzedne());
        rec.setTexture(&this->teksturaj);
    };
    virtual void draw(sf::RenderTarget& cel, sf::RenderStates) const
        {
            cel.draw(rec);
        };

    void TeksturaJablka(sf::Texture tekstura)
    {

           Tekstura(tekstura);
    };



private:

sf::Texture teksturaj;
void Tekstura(sf::Texture tekstura)
{
    this->teksturaj = tekstura;
};



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
            rec.setTexture(&this->teksturaj);
            rec.setFillColor(sf::Color(170,0,0));

            return -losujrozmiar;
        }
        else {

            rec.setTexture(&this->teksturaj);
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
        rec.setFillColor(sf::Color::Red);
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
        rec.setFillColor(sf::Color::Red);
        uszkodzenie = true;
    };
    void dezintegracja()
    {
        rec.setFillColor(sf::Color::Black);
        uszkodzenie = false;
    };


};
class Game
{
public:
    Game(sf::RenderWindow &window, Informacje &informacje, sf::Font czcionka, sf::Texture tekstura)
    {
        this->tekstura = tekstura;
        this->czcionka = czcionka;
        this->informacje = &informacje;
        this->window = &window;
        tempo = N;
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
                    if(event.key.code == sf::Keyboard::Space){
                        if(tempo == N){
                            tempo = W;
                            dzwieki.play(Dzwiek::WOLNO);
                        }
                        else{tempo = N;dzwieki.play(Dzwiek::SZYBKO);}
                    if(event.key.code == sf::Keyboard::B){informacje->funkcja = Informacje::MENU;}

                    }
                }
            }

            refresh();
            stanjablka();
            refreshpocisk();


            czesc.ustawTekstura(tekstura);
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
            //window->draw(interface);
            window->draw(waz);
            window->draw(pocisk.rec);

            for(size_t i=0; i<jablka.size(); i++)
            {
                window->draw(jablka[i]);
            }

            window->display();
        }
    };
private:
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

sf::Clock Rclock;
sf::Time Rela;
sf::Time RTR;
enum Tempo { N = 10, W = 50 };
Tempo tempo;
void refresh()
    {
        Rela =Rclock.getElapsedTime();
        RTR = sf::milliseconds(tempo);

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
    JTR = sf::seconds(czasgenjablka);
    Jela = Jclock.getElapsedTime();

    if(Jela > JTR){
        Jclock.restart();
        return true;
    }
    return 0;
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
                    waz.rozmiarwaz(jablka[i].zmianadlugosci);
                }
                else {
                    waz.rozmiarwaz(waz.dlugosc * -1);
                }

                usun(i);
            }
        }
    };
void usun(int itemNumber)
    {
       jablka.erase(jablka.begin() + itemNumber);
    }
    ;
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
            dzwieki.play(Dzwiek::POCISK);
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
        PTR = sf::seconds(czaspocisku);
        Pela = Pclock.getElapsedTime();

        if(Pela > PTR){
            Pclock.restart();
            return true;
        }
        else {
            return false;
        }
    };
void obciecie()
    {
        if(pocisk.uszkodzenie){
            for(size_t i=0; i<waz.czesci.size(); i++)
            {
                if(kolizja.JestKolizja(pocisk, waz.czesci[i])){
                    waz.rozmiarwaz(-1 * (waz.czesci.size()-i-1));
                }
            }
        }
    };
    static constexpr float czasgenjablka = 3.0;
    static constexpr float czaspocisku = 5;
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
class Okno
{
public:
    virtual void pokaz() = 0;
protected:

sf::RenderWindow *window;
sf::Font czcionka;
sf::Text naglowek;
std::string tresc;
Informacje *informacje;
sf::Text *funkcje;
std::string *opcjestr;
void ustawienianaglowka()
    {
        naglowek.setFont(czcionka);
        naglowek.setCharacterSize(80);
        naglowek.setString(tresc);
        naglowek.setPosition(wysrodkowanie(naglowek)+50,60);
        naglowek.setFillColor(sf::Color::Blue);
    };

void zmianakoloru(sf::Vector2f &wspolzednem) const
{
    for(int i=0; i<iloscopcji; i++)
    {
        if(funkcje[i].getGlobalBounds().contains(wspolzednem)){
            funkcje[i].setFillColor(sf::Color::Red);
        }
        else{
            funkcje[i].setFillColor(sf::Color::Black);
        }
    }
};
int iloscopcji;
void funkcjeprzyciskow()
    {
        for(int i=0; i<iloscopcji; i++)
        {
            funkcje[i].setFont(czcionka);
            funkcje[i].setString(opcjestr[i]);
            funkcje[i].setCharacterSize(50);
            funkcje[i].setPosition(wysrodkowanie(funkcje[i]), 2*60 + 100*(i+1));
            funkcje[i].setFillColor(sf::Color::Black);
        }
    };
float wysrodkowanie(sf::Text &text) const
    {
        return Informacje::SzerokoscOkna/2 - text.getGlobalBounds().width/2;
    };

};
class Menu : Okno
{
public:
virtual void pokaz()
    {
        while(informacje->funkcja == Informacje::MENU)
        {
            sf::Vector2f wspolzednem(sf::Mouse::getPosition(*window));
            sf::Event event;

            while(window->pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed && event.key.code == (sf::Keyboard::Escape|| event.type == sf::Event::Closed)){
                    informacje->funkcja = Informacje::KONIEC;
                }

                if(event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left){
                    if(funkcje[0].getGlobalBounds().contains(wspolzednem)){
                        informacje->funkcja = Informacje::GRA;
                    }
                    else if(funkcje[1].getGlobalBounds().contains(wspolzednem)){
                        informacje->funkcja = Informacje::KONIEC;
                    }
                }
            }
            zmianakoloru(wspolzednem);
            sf::Sprite sprite_grass;
            sprite_grass.setTexture(tekstura);
            tekstura.setRepeated(true);
            sprite_grass.setTextureRect(sf::IntRect(0, 0, 800, 600));
            window->clear(sf::Color::White);
            window->draw(sprite_grass);
            window->draw(naglowek);
            for(int i=0; i<iloscopcji; i++)
            {
                window->draw(funkcje[i]);
            }

            window->display();
        }
    };
 Menu(sf::RenderWindow &window, Informacje &informacje, sf::Font czcionka,sf::Texture tekstura)
    {
        this->window = &window;
        this->tekstura = tekstura;
        this->czcionka = czcionka;
        this->informacje = &informacje;

        tresc = Informacje::NazwaGry;

        iloscopcji = 2;
        funkcje = new sf::Text[iloscopcji];
        opcjestr = new std::string[iloscopcji];
        opcjestr[0] = "GRAJ";
        opcjestr[1] = "WYJSCIE";

        ustawienianaglowka();
        funkcjeprzyciskow();
    };
~Menu()
    {
        delete[] funkcje;
        delete[] opcjestr;
    };

private:
    sf::Texture tekstura;

};
class Wynik : Okno
{
public:
    virtual void pokaz()
    {
        while(informacje->funkcja == Informacje::WYNIK)
        {
            sf::Vector2f wspolzednem(sf::Mouse::getPosition(*window));
            sf::Event event;
            while(window->pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape|| event.type == sf::Event::Closed)){
                    informacje->funkcja = Informacje::KONIEC;
                }

                if(event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left){
                    if(funkcje[0].getGlobalBounds().contains(wspolzednem)){
                        informacje->funkcja = Informacje::GRA;
                    }
                    else if(funkcje[1].getGlobalBounds().contains(wspolzednem)){
                        informacje->funkcja = Informacje::MENU;
                    }
                }
            }
            zmianakoloru(wspolzednem);
            sf::Sprite sprite_grass;
            sprite_grass.setTexture(tekstura);
            tekstura.setRepeated(true);
            sprite_grass.setTextureRect(sf::IntRect(0, 0, 800, 600));

            window->clear(sf::Color::White);
            window->draw(sprite_grass);
            window->draw(naglowek);

            for(int i=0; i<iloscopcji; i++)
            {
                window->draw(funkcje[i]);
            }

            window->display();
        }
    };
Wynik(sf::RenderWindow &window, Informacje &informacje, sf::Font czcionka, sf::Texture tekstura)
    {
        this->window = &window;
        this->tekstura = tekstura;
        this->czcionka = czcionka;
        this->informacje = &informacje;



        std::string wynik = Informacje::convertIntToString(informacje.wynik);
        std::string text = "TWOJ WYNIK: ";
        tresc = text + wynik;

        iloscopcji = 2;
        funkcje = new sf::Text[iloscopcji];
        opcjestr = new std::string[iloscopcji];
        opcjestr[0] = "SPROBOJ PONOWNIE";
        opcjestr[1] = "POWROT DO MENU";

        ustawienianaglowka();
        funkcjeprzyciskow();
    };
~Wynik()
    {
        delete[] funkcje;
        delete[] opcjestr;
    };

protected:
    sf::Texture tekstura;
};
class Inicjalizacja
{
public:
    Inicjalizacja()
    {
        window.create(sf::VideoMode(Informacje::SzerokoscOkna,Informacje::WysokoscOkna),Informacje::NazwaGry);
        lczcionka();
        loadTexture();
        srand(time(NULL));
    };
void start(){
        while(window.isOpen())
        {
            if(informacje.funkcja == Informacje::GRA){startgry();}
            if(informacje.funkcja == Informacje::MENU){menu();}
            if(informacje.funkcja == Informacje::WYNIK){wynik();}
            if(informacje.funkcja == Informacje::KONIEC){window.close();}
        }
    };
private:
sf::RenderWindow window;
Jablko jablko;
Informacje informacje;
sf::Font czcionka;
sf::Texture tekstura;
sf::Texture tekstura2;
sf::Texture tekstura3;
sf::Texture tekstura4;
Dzwiek audioController;

    void loadTexture()
    {
        //tekstura.loadFromFile("Texture/hero.png");
        //tekstura2.loadFromFile("Texture/wall.png");
        tekstura3.loadFromFile("Texture/grass.png");
        //tekstura4.loadFromFile("Texture/monster.png");
    };

void lczcionka()
    {
        czcionka.loadFromFile("data/Bleeding_Cowboys.ttf");
    };
void startgry()
    {
        Game game(window, informacje, czcionka, tekstura3);
        audioController.play(Dzwiek::MUS2);
        game.start();
    };
void menu()
    {
        Menu Menu(window, informacje, czcionka, tekstura3);
        audioController.play(Dzwiek::MUS1);
        Menu.pokaz();
    };
void wynik()
    {
        Wynik vScore(window, informacje, czcionka, tekstura3);
        audioController.play(Dzwiek::MUS1);
        vScore.pokaz();
    };
};

int main()
{
   Inicjalizacja uruchom;
   uruchom.start();
   return 0;
}
