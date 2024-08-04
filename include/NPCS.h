#ifndef NPCS_HPP
#define NPCS_HPP

#include "NPC.hpp"
#include <vector>

class NPCS {
private:
    std::vector<NPC> npcs;
public:
    void make();
    void update(sf::RenderWindow& window, sf::Sound& gun);
    void draw(sf::RenderWindow& window);
    void reset();
};

#endif // NPCS_HPP
