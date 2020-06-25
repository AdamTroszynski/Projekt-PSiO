#ifndef KOLIZJA_H
#define KOLIZJA_H
#include <vector>
#include <SFML/Graphics.hpp>
class Przeszkoda
{
public:
    sf::RectangleShape rec;
    sf::Vector2f getPosition(){return rec.getPosition();}
    sf::Vector2f getSize(){return rec.getSize();};
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
#endif // KOLIZJA_H
