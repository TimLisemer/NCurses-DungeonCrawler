#include "character.h"
#include "tile.h"
#include <ncurses.h>
#include "logger.h"

Character::Character(Controller* controller, Level* level, const char icon, const int strenght, const int stamina) : m_controller(controller), m_level(level), m_icon(icon), m_strenght(strenght), m_stamina(stamina){}

//delete Character
Character::~Character(){
    delete m_position;
    delete m_controller;
    delete m_level;

    for(size_t i = 0; i < m_items.size(); i++){
        delete m_items.at(i);
    }
}

int Character::move(){
    return m_controller->move(this);
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

void Character::setHitPoints(const int hitPoints){
    m_hitPoints = hitPoints;
}


int Character::getMaxHP() const{
    return (20 + (m_stamina*5)) * m_maxHpMultiplier;
}


void Character::setMaxHpMultiplier(const int multiplier){
    m_maxHpMultiplier = multiplier;
}


void Character::addToInventory(Item *item){
    item->onEquip(this);
    m_items.push_back(item);
}


int Character::getInventorySize() const{
    return m_items.size();
}


Level* Character::getLevel() const{
    return m_level;
}































