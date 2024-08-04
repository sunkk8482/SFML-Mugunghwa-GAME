#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Her.hpp"
#include "NPCS.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 1490;
const int WINDOW_HEIGHT = 400;
const float MAX_GAME_TIME = 149.0f;

int seeMode = 0;
int gameStarted = 0;
int gameWon = 0;
int allDead = 0;
Clock playTime;
int __time = 149;

void printText(Text& textMsg, Font& font, int size, float x, float y, const Color& color, const Color& outColor, const string& p) {
    textMsg.setFont(font);
    textMsg.setCharacterSize(size);
    textMsg.setPosition(x, y);
    textMsg.setFillColor(color);
    textMsg.setOutlineColor(outColor);
    textMsg.setString(p);
}

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "mugung");
    window.setFramerateLimit(200);

    RectangleShape ground(Vector2f(WINDOW_WIDTH, 10));
    ground.setPosition(0, 390);
    ground.setFillColor(Color::Yellow);

    Texture backgroundTexture, pressTexture, victoryTexture;
    backgroundTexture.loadFromFile("background.png");
    pressTexture.loadFromFile("press.png");
    victoryTexture.loadFromFile("victory.png");

    Sprite backgroundSprite(backgroundTexture);
    Sprite pressSprite(pressTexture);
    Sprite victorySprite(victoryTexture);

    SoundBuffer buffer1, buffer2, buffer3, buffer4, backMusicBuffer, degiMusicBuffer, gunBuffer;
    buffer1.loadFromFile("sou.wav");
    buffer2.loadFromFile("sou2.wav");
    buffer3.loadFromFile("sou4.wav");
    buffer4.loadFromFile("sou8.wav");
    backMusicBuffer.loadFromFile("backmusic.wav");
    degiMusicBuffer.loadFromFile("degimusic.wav");
    gunBuffer.loadFromFile("GUNSHOT.wav");

    Sound sound1(buffer1), sound2(buffer2), sound3(buffer3), sound4(buffer4);
    Sound backMusic(backMusicBuffer), degiMusic(degiMusicBuffer), gunSound(gunBuffer);

    backMusic.setVolume(60);
    degiMusic.play();

    Font font;
    Text textMessage;

    if (!font.loadFromFile("DS_DIGIB.ttf")) {
        cout << "Font loading error!" << endl;
        return -1;
    }

    Event event;

    Player player;
    Her her;
    NPCS npcs;
    for (int i = 0; i < 20; ++i) {
        npcs.make();
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        string timeString = "Time : " + to_string(__time - static_cast<int>(playTime.getElapsedTime().asSeconds()));

        if (gameStarted == 1 && gameWon == 0) {
            if (playTime.getElapsedTime().asSeconds() > MAX_GAME_TIME) {
                allDead = 1;
            }
            window.draw(backgroundSprite);
            window.draw(ground);
            printText(textMessage, font, 60, 500, 100, Color::Black, Color::Black, timeString);
            window.draw(textMessage);

            her.draw(window, sound1, sound2, sound3, sound4);
            npcs.update(window, gunSound);
            npcs.draw(window);
            player.update(window, gunSound, degiMusic);
        }
        else if (gameStarted == 0 && gameWon == 0) {
            backMusic.stop();
            window.draw(pressSprite);
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                degiMusic.stop();
                playTime.restart();
                player.reset();
                npcs.reset();
                gameStarted = 1;
                allDead = 0;
                backMusic.play();
            }
        }
        else if (gameWon == 1) {
            window.draw(victorySprite);
            backMusic.stop();
            sound1.stop();
            sound2.stop();
            sound3.stop();
            sound4.stop();
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                degiMusic.play();
                gameStarted = 0;
                gameWon = 0;
            }
        }

        window.display();
    }

    return 0;
}
