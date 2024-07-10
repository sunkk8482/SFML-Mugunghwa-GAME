#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player {
private:
    int moveMode = 0;
    float x = 0;
    float y = 300;
    int death = 0;
    int frame = 0;
    int deathFrame = 0;
    sf::Clock frameTime;
    sf::Clock deathFrameTime;
public:
    sf::Sprite sprite;
    sf::Texture texture;

    void draw(sf::RenderWindow& window, sf::Sound& sound);
    void update(sf::RenderWindow& window, sf::Sound& gun, sf::Sound& sound);
    void reset();
};

#endif // PLAYER_HPP
