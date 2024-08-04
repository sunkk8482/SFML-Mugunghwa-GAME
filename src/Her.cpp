#include "Her.hpp"
#include <iostream>

extern int seeMode;

Her::Her() {
    nonSee = rand() % 3;
}

void Her::makeRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 7);
    nonSee = dis(gen);
}

void Her::makeRandSound() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 3);
    randSound = dis(gen);
}

void Her::makeSound(sf::Sound& sou, sf::Sound& sou2, sf::Sound& sou4, sf::Sound& sou8) {
    if (randSound == 0) {
        sou.play();
    }
    else if (randSound == 1) {
        sou2.play();
    }
    else if (randSound == 2) {
        sou4.play();
    }
    else if (randSound == 3) {
        sou8.play();
    }
}

void Her::draw(sf::RenderWindow& window, sf::Sound& sou, sf::Sound& sou2, sf::Sound& sou4, sf::Sound& sou8) {
    sprite.setPosition(x, y);
    switch (seeMode) {
    case 0:
        if (nonSeeTime.getElapsedTime().asSeconds() > nonSee) {
            seeMode = 1;
        }
        texture.loadFromFile("nonsee.png");
        sprite.setTexture(texture);
        window.draw(sprite);
        break;
    case 1:
        texture.loadFromFile("nonsee.png");
        sprite.setTexture(texture);
        window.draw(sprite);
        makeSound(sou, sou2, sou4, sou8);
        makeRandom();
        singTime.restart();
        seeMode = 2;
        break;
    case 2:
        texture.loadFromFile("nonsee.png");
        sprite.setTexture(texture);
        window.draw(sprite);

        if ((randSound == 0 && singTime.getElapsedTime().asSeconds() > 6.5) ||
            (randSound == 1 && singTime.getElapsedTime().asSeconds() > 3.25) ||
            (randSound == 2 && singTime.getElapsedTime().asSeconds() > 1.625) ||
            (randSound == 3 && singTime.getElapsedTime().asSeconds() > 1)) {
            makeRandSound();
            seeMode = 3;
            seeTime.restart();
        }
        break;
    case 3:
        texture.loadFromFile("see.png");
        sprite.setTexture(texture);
        window.draw(sprite);
        if (seeTime.getElapsedTime().asSeconds() > 3) {
            nonSeeTime.restart();
            seeMode = 0;
        }
        break;
    }
}
