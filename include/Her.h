#ifndef HER_HPP
#define HER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

class Her {
private:
    float x = 1300;
    float y = 30;
    sf::Clock seeTime;
    sf::Clock nonSeeTime;
    sf::Clock singTime;
public:
    sf::Sprite sprite;
    sf::Texture texture;
    int see = 0;
    int nonSee = 0;
    int randSound = 0;

    Her();
    void makeRandom();
    void makeRandSound();
    void makeSound(sf::Sound& sou, sf::Sound& sou2, sf::Sound& sou4, sf::Sound& sou8);
    void draw(sf::RenderWindow& window, sf::Sound& sou, sf::Sound& sou2, sf::Sound& sou4, sf::Sound& sou8);
};

#endif // HER_HPP
