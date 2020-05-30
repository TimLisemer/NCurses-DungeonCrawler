#include "character.h"
#include "tile.h"
#include <ncurses.h>
#include "logger.h"

Character::Character(const char icon, Controller* controller) : m_icon(icon), m_controller(controller){}

char Character::getIcon() const {
    return m_icon;
}

void Character::setTile(Tile *tile) {
    m_position = tile;
}

Tile* Character::getTile() {
    return m_position;
}

int Character::move(){
    return m_controller->move();
}
