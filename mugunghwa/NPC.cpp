#include "NPC.hpp"
#include <iostream>

extern int seeMode;
extern int gameStarted;
extern int allDead;

NPC::NPC() {
    resetPosition();
    makeRandom();
}

void NPC::resetPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 200);
    x = dis(gen);
}

void NPC::makeRandom() {
    if (seeMode < 2) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 1);
        button = dis(gen);
    }
    else if (seeMode == 3) {
        return;
    }
    else if (seeMode == 2) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 10);
        button = dis(gen);
    }
}

void NPC::draw(sf::RenderWindow& window) {
    sprite.setPosition(x, y);
    if (death == 0) {
        texture.loadFromFile("npcmove.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0 + frame, 0, 100, 100));

        if (frameTime.getElapsedTime().asSeconds() > 0.05 && moveMode == 1) {
            frame = (frame + 100) % 400;
            frameTime.restart();
        }
    }
    else {
        texture.loadFromFile("npcdeath.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0 + deathFrame, 0, 100, 100));

        if (deathFrameTime.getElapsedTime().asSeconds() > 0.05 && deathFrame < 500) {
            deathFrame += 100;
            deathFrameTime.restart();
        }
    }
    window.draw(sprite);
}

void NPC::update(sf::RenderWindow& window, sf::Sound& gun) {
    if (allDead == 1) {
        death = 1;
    }
    if (death == 1) {
        return;
    }

    if (gameStarted == 1 && buttonTime.getElapsedTime().asSeconds() > 2.5) {
        makeRandom();
        buttonTime.restart();
    }

    if (button == 1 && death == 0) {
        if (seeMode == 3) {
            gun.play();
            death = 1;
            deathFrameTime.restart();
        }
        moveMode = 1;
        x += 1.1f;
    }
    else {
        moveMode = 0;
    }

    draw(window);
}

void NPC::reset() {
    death = 0;
    resetPosition();
    moveMode = 0;
    deathFrame = 0;
    frame = 0;
}
