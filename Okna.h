#ifndef OKNA_H
#define OKNA_H
#include <SFML/Graphics.hpp>
#include <informacje.h>
class oknomenu
{
public:
    void pokaz()
    {
        while(informacje->funkcja == Informacje::MENU)
        {
            sf::Vector2f wspolzednem(sf::Mouse::getPosition(*window));
            sf::Event event;

            while(window->pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == (sf::Keyboard::Escape)){
                        informacje->funkcja = Informacje::KONIEC;
                    }
                }
                if(event.type == sf::Event::MouseButtonReleased){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(funkcje[0].getGlobalBounds().contains(wspolzednem)){
                            informacje->funkcja = Informacje::GRA;
                        }
                        else if(funkcje[1].getGlobalBounds().contains(wspolzednem)){
                            informacje->funkcja = Informacje::KONIEC;
                        }
                        else if(funkcje[2].getGlobalBounds().contains(wspolzednem)){informacje->funkcja = Informacje::POMOC;};
                    }
                }
            }
            zmianakoloru(wspolzednem);
            sf::Sprite sprite_grass;
            sprite_grass.setTexture(tekstura);
            tekstura.setRepeated(true);
            tekstura.setSmooth(true);
            sprite_grass.setTextureRect(sf::IntRect(0, 0, Informacje::SzerokoscOkna, Informacje::WysokoscOkna));
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
    oknomenu(sf::RenderWindow &window, Informacje &informacje, sf::Font czcionka, sf::Texture tekstura)
    {
        tresc = Informacje::NazwaGry;
        this->window = &window;
        this->tekstura = tekstura;
        this->czcionka = czcionka;
        this->informacje = &informacje;

        ustawienianaglowka();


        iloscopcji = 3;
        funkcje = new sf::Text[iloscopcji];
        opcjestr = new std::string[iloscopcji];
        opcjestr[0] = "GRAJ";
        opcjestr[1] = "WYJSCIE";
        opcjestr[2] = "POMOC";
        funkcjeprzyciskow();

    };

    void ustawienianaglowka()
    {
        naglowek.setFont(czcionka);
        naglowek.setCharacterSize(80);
        naglowek.setString(tresc);
        naglowek.setPosition(wysrodkowanie(naglowek)+50,60);
        naglowek.setFillColor(sf::Color(255,255,0));
    };
    void funkcjeprzyciskow()
    {
        for(int i=0; i<iloscopcji; i++)
        {
            funkcje[i].setFont(czcionka);
            funkcje[i].setString(opcjestr[i]);
            funkcje[i].setCharacterSize(50);
            funkcje[i].setPosition(wysrodkowanie(funkcje[i]), 2*60 + 100*(i+1));
            funkcje[i].setFillColor(sf::Color(0,0,0));
        }
    };
    void zmianakoloru(sf::Vector2f &wspolzednem) const
    {
        for(int i=0; i<iloscopcji; i++)
        {
            if(funkcje[i].getGlobalBounds().contains(wspolzednem)){
                funkcje[i].setFillColor(sf::Color(255,0,0));

            }
            else{
                funkcje[i].setFillColor(sf::Color(255,255,255));
            }
        }
    };

    sf::Font czcionka;
    std::string tresc;
    Informacje *informacje;
    sf::Text *funkcje;
    std::string *opcjestr;
    sf::RenderWindow *window;
    sf::Texture tekstura;
    sf::Text naglowek;
    int iloscopcji;
    float wysrodkowanie(sf::Text &text) const
    {
        return Informacje::SzerokoscOkna/2 - text.getGlobalBounds().width/2;
    };



};
class oknopomocy
{
public:
    void pokaz(){
        {
            while(informacje->funkcja == Informacje::POMOC)
            {
                sf::Vector2f wspolzednem(sf::Mouse::getPosition(*window));
                sf::Event event;
                while(window->pollEvent(event))
                {
                    if(event.type == sf::Event::KeyPressed)
                        if(event.key.code == sf::Keyboard::Escape){
                            informacje->funkcja = Informacje::KONIEC;
                        }

                    if(event.type == sf::Event::MouseButtonReleased){
                        if(event.mouseButton.button == sf::Mouse::Left){
                            if(funkcje[0].getGlobalBounds().contains(wspolzednem)){
                                informacje->funkcja = Informacje::GRA;
                            }
                            else if(funkcje[1].getGlobalBounds().contains(wspolzednem)){
                                informacje->funkcja = Informacje::MENU;
                            }
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
                window->draw(naglowek2);

                for(int i=0; i<iloscopcji; i++)
                {
                    window->draw(funkcje[i]);
                }

                window->display();
            }
        };
    }
    oknopomocy(sf::RenderWindow &window, Informacje &informacje, sf::Font czcionka, sf::Texture tekstura)
    {
        this->window = &window;
        this->tekstura = tekstura;
        this->czcionka = czcionka;
        this->informacje = &informacje;

        std::string text = "Poruszanie sie wezem jest realizowanie przez przyciski:\n W gora, A lewo, D prawo, S dol\n Zbieraj tylko zielone jablka, czerwone sa zle\n oraz uwazaj na pociski ktore cie moga zranic";
        tresc = text;

        ustawienianaglowkap();


        iloscopcji = 2;
        funkcje = new sf::Text[iloscopcji];
        opcjestr = new std::string[iloscopcji];
        opcjestr[0] = "GRAJ";
        opcjestr[1] = "POWROT DO MENU";
        funkcjeprzyciskowp();

    };
    void ustawienianaglowkap()
    {
        naglowek2.setFont(czcionka);
        naglowek2.setCharacterSize(25);
        naglowek2.setString(tresc);
        naglowek2.setPosition(wysrodkowanie(naglowek2),60);
        naglowek2.setFillColor(sf::Color(255,255,0));
    };
    void funkcjeprzyciskowp()
    {
        for(int i=0; i<iloscopcji; i++)
        {
            funkcje[i].setFont(czcionka);
            funkcje[i].setString(opcjestr[i]);
            funkcje[i].setCharacterSize(50);
            funkcje[i].setPosition(wysrodkowanie(funkcje[i]), 2*100 + 100*(i+1));
            funkcje[i].setFillColor(sf::Color(255,255,255));
        }
    };
    void zmianakoloru(sf::Vector2f &wspolzednem) const
    {
        for(int i=0; i<iloscopcji; i++)
        {
            if(funkcje[i].getGlobalBounds().contains(wspolzednem)){
                funkcje[i].setFillColor(sf::Color(255,0,0));
            }
            else{
                funkcje[i].setFillColor(sf::Color(255,255,255));
            }
        }
    };
protected:
    sf::Font czcionka;
    std::string tresc;
    Informacje *informacje;
    sf::Text *funkcje;
    std::string *opcjestr;
    sf::RenderWindow *window;
    sf::Text naglowek2;
    sf::Texture tekstura;
    int iloscopcji;
    float wysrodkowanie(sf::Text &text) const
        {
            return Informacje::SzerokoscOkna/2 - text.getGlobalBounds().width/2;
        };


};
class oknowyniku
{
public:
    void pokaz()
    {
        while(informacje->funkcja == Informacje::WYNIK)
        {
            sf::Vector2f wspolzednem(sf::Mouse::getPosition(*window));
            sf::Event event;
            while(window->pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Escape){
                        informacje->funkcja = Informacje::KONIEC;
                    }
                }

                if(event.type == sf::Event::MouseButtonReleased){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        if(funkcje[0].getGlobalBounds().contains(wspolzednem)){
                            informacje->funkcja = Informacje::GRA;
                        }
                        else if(funkcje[1].getGlobalBounds().contains(wspolzednem)){
                            informacje->funkcja = Informacje::MENU;
                        }
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
    oknowyniku(sf::RenderWindow &window, Informacje &informacje, sf::Font czcionka, sf::Texture tekstura)
    {
        this->window = &window;
        this->tekstura = tekstura;
        this->czcionka = czcionka;
        this->informacje = &informacje;

        std::string wynik = Informacje::zmianaintnastr(informacje.wynik);
        std::string text = "TWOJ WYNIK: ";
        tresc = text + wynik;

        ustawienianaglowka();


        iloscopcji = 2;
        funkcje = new sf::Text[iloscopcji];
        opcjestr = new std::string[iloscopcji];
        opcjestr[0] = "SPROBOJ PONOWNIE";
        opcjestr[1] = "POWROT DO MENU";
        funkcjeprzyciskow();

    };
    void ustawienianaglowka()
    {
        naglowek.setFont(czcionka);
        naglowek.setCharacterSize(80);
        naglowek.setString(tresc);
        naglowek.setPosition(wysrodkowanie(naglowek)+50,60);
        naglowek.setFillColor(sf::Color::Blue);
    };
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
protected:
    sf::Font czcionka;
    std::string tresc;
    Informacje *informacje;
    sf::Text *funkcje;
    std::string *opcjestr;
    sf::RenderWindow *window;
    sf::Texture tekstura;
    sf::Text naglowek;
    int iloscopcji;
    float wysrodkowanie(sf::Text &text) const
    {
        return Informacje::SzerokoscOkna/2 - text.getGlobalBounds().width/2;
    };


};
#endif // OKNA_H
