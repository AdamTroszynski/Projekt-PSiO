#ifndef DZWIEK_H
#define DZWIEK_H
#include <SFML/Audio.hpp>
class Dzwiek
{
public:
    enum Dzwieki {OKNA, GRA, POCISK};

    Dzwiek()
    {
        ldzwiek();
    };
    void odtworz(Dzwieki muzyka)
    {
        if(muzyka == OKNA){
            m1dzwiek.play();
            m2dzwiek.stop();
        }
        if(muzyka == GRA){
            m1dzwiek.stop();
            m2dzwiek.play();
        }
        if(muzyka == POCISK){
            s3dzwiek.play();
        }
    };
    void ldzwiek()
    {
        m1dzwiek.openFromFile("Baza/Ending.wav");
        m2dzwiek.openFromFile("Baza/TitleScreen.wav");
        m1dzwiek.setLoop(true);
        m2dzwiek.setLoop(true);
        sB3dzwiek.loadFromFile("Baza/strzal.wav");
        s3dzwiek.setBuffer(sB3dzwiek);
    };
    sf::SoundBuffer sB3dzwiek;
    sf::Sound s3dzwiek;
    sf::Music m1dzwiek;
    sf::Music m2dzwiek;

};
#endif // DZWIEK_H
