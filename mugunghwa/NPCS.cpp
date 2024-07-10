#include "NPCS.hpp"

void NPCS::make() {
    NPC npc;
    npcs.push_back(npc);
}

void NPCS::update(sf::RenderWindow& window, sf::Sound& gun) {
    for (auto& npc : npcs) {
        npc.update(window, gun);
    }
}

void NPCS::draw(sf::RenderWindow& window) {
    for (auto& npc : npcs) {
        npc.draw(window);
    }
}

void NPCS::reset() {
    for (auto& npc : npcs) {
        npc.reset();
    }
}
