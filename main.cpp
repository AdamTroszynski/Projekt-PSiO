#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
class Baza
{
public:
static constexpr const char* NazwaGry = "Snake";
static const int snakePartSize = 3;
static const int energyLimit = 100;
static const int WysokoscOkna = 600;
static const int SzerokoscOkna = 800;


};
class Uruchom{
public:
    Uruchom()
    {
        window.create(sf::VideoMode(Baza::SzerokoscOkna,Baza::WysokoscOkna),Baza::NazwaGry);
        srand(time(NULL));
    };
    void start()
    {
        {
            while(window.isOpen())
            {

            }
        }
    };

private:
    sf::RenderWindow window;
    sf::Font czcionka;
};
int main()
{
    Uruchom uruchom;
            uruchom.start();
};
