#include "character.h"
#include "tile.h"
#include <ncurses.h>
#include "logger.h"

Character::Character(Controller* controller, const char icon, const int strenght, const int stamina) : m_controller(controller), m_icon(icon), m_strenght(strenght), m_stamina(stamina){}

//delete Character
Character::~Character(){
    delete m_position;
    delete m_controller;
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



char Character::getIcon() const {
    return m_icon;
}

void Character::setIcon(const char icon){
    m_icon = icon;
}

int Character::getStrenght() const{
    return m_strenght;
}

void Character::setStrenght(const int strenght){
    m_strenght = strenght;
}


int Character::getStamina() const{
    return m_stamina;
}

void Character::setStamina(const int stamina){
    m_stamina = stamina;
}


int Character::getHitPoints() const{
    return m_hitPoints;
}

int Character::getMaxHP() const{
    return 20 + (m_hitPoints*5);
}

void Character::setHitPoints(const int hitPoints){
    m_hitPoints = hitPoints;
}


































