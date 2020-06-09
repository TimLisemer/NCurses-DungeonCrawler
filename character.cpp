#include "character.h"
#include "tile.h"
#include <ncurses.h>
#include "logger.h"

Character::Character(const char icon, Controller* controller) : m_icon(icon), m_controller(controller){}

//delete Character
Character::~Character(){
    delete m_position;
    delete m_controller;
}

char Character::getIcon() const {
    return m_icon;
}

void Character::setIcon(const char icon){
    m_icon = icon;
}

void Character::setTile(Tile *tile) {
    m_position = tile;
}

Tile* Character::getTile() const{
    return m_position;
}

Controller* Character::getController() const{
    return m_controller;
}

void Character::setController(Controller *controller){
    m_controller = controller;
}

int Character::move(){
    return m_controller->move();
}
