#include "Player.hpp"
#include <iostream>

extern int seeMode;
extern int gameStarted;
extern int gameWon;
extern int allDead;

void Player::draw(sf::RenderWindow& window, sf::Sound& sound) {
    if (x > 1400) {
        gameWon = 1;
    }

    sprite.setPosition(x, y);

    if (death == 0) {
        texture.loadFromFile("mymove.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0 + frame, 0, 100, 100));

        if (frameTime.getElapsedTime().asSeconds() > 0.05 && moveMode == 1) {
            frame = (frame + 100) % 400;
            frameTime.restart();
        }
    }
    else {
        texture.loadFromFile("mydeath.png");
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0 + deathFrame, 0, 100, 100));

        if (deathFrameTime.getElapsedTime().asSeconds() > 0.05 && deathFrame < 500) {
            deathFrame += 100;
            deathFrameTime.restart();
        }
        if (deathFrameTime.getElapsedTime().asSeconds() > 3) {
            gameStarted = 0;
            sound.play();
        }
    }

    window.draw(sprite);
}

void Player::update(sf::RenderWindow& window, sf::Sound& gun, sf::Sound& sound) {
    if (death == 1) {
        return;
    }
    if (allDead == 1) {
        gun.play();
        death = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && death == 0) {
        if (seeMode == 3) {
            gun.play();
            death = 1;
            deathFrameTime.restart();
        }
        moveMode = 1;
        x += 0.8f;
    }
    else {
        moveMode = 0;
    }
    draw(window, sound);
}

void Player::reset() {
    death = 0;
    x = 0;
    moveMode = 0;
    deathFrame = 0;
    frame = 0;
}
