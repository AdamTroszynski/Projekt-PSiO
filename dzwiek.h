#ifndef DZWIEK_H
#define DZWIEK_H
#include <SFML/Audio.hpp>
class Dzwiek
{
public:
    enum Dzwieki {OKNA, GRA, WOLNO, SZYBKO, POCISK};

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
        if(muzyka == SZYBKO){
            s2dzwiek.play();
        }
        if(muzyka == WOLNO){
            s1dzwiek.play();
        }
        if(muzyka == POCISK){
            s3dzwiek.play();
        }
    };
    void ldzwiek()
    {
        m1dzwiek.openFromFile("data/Ending.wav");
        m2dzwiek.openFromFile("data/TitleScreen.wav");
        m1dzwiek.setLoop(true);
        m2dzwiek.setLoop(true);
        sB1dzwiek.loadFromFile("data/slowDown");
        s1dzwiek.setBuffer(sB1dzwiek);
        sB2dzwiek.loadFromFile("data/speedUp");
        s2dzwiek.setBuffer(sB2dzwiek);
        sB3dzwiek.loadFromFile("data/laserShot");
        s3dzwiek.setBuffer(sB2dzwiek);
    };

    sf::SoundBuffer sB1dzwiek;
    sf::SoundBuffer sB2dzwiek;
    sf::SoundBuffer sB3dzwiek;
    sf::Sound s1dzwiek;
    sf::Sound s2dzwiek;
    sf::Sound s3dzwiek;
    sf::Music m1dzwiek;
    sf::Music m2dzwiek;

};
#endif // DZWIEK_H
