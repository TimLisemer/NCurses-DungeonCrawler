#include "character.h"
#include "tile.h"
#include <ncurses.h>
#include "logger.h"

Character::Character(char icon) : m_icon(icon)
{

}

char Character::getIcon() const {
    return m_icon;
}

void Character::setTile(Tile *tile) {
    m_position = tile;
}

Tile* Character::getTile() {
    return m_position;
}

int Character::move() {
    mvaddstr(0,25, "1-9 to Move, press 0 to close");
    int key = getch();
    //return the key, check in main game loop if the game should continue
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "return " + std::to_string(key));
    return key;
}
