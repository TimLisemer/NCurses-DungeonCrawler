#include "character.h"
#include "tile.h"
#include <ncurses.h>
#include "logger.h"

// @TODO: Add more Items
Character::Character(Controller* controller, Level* level, const char icon, const int strenght, const int stamina, const bool human) : m_controller(controller), m_level(level), m_icon(icon),
    m_strenght(strenght), m_stamina(stamina), m_hitPoints(20 + (m_stamina*5)), m_Human(human){}

//delete Character
Character::~Character(){
    delete m_controller;
    for(size_t i = 0; i < m_items.getSize(); i++){
        delete m_items[i];
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
    return ((20 + (m_stamina*5)) * m_maxHpMultiplier) + m_maxHPBuffer;
}

int Character::getMaxHPBuffer() const{
    return m_maxHPBuffer;
}

void Character::setMaxHpMultiplier(const double multiplier){
    m_maxHpMultiplier = multiplier;
    if(getHitPoints() > getMaxHP()){
        setHitPoints(getMaxHP());
    }
}

void Character::setMaxHpBuffer(const int buffer){
    m_maxHPBuffer = buffer;
}


void Character::addToInventory(Item *item){
    item->onEquip(this);
    m_items.pushBack(item);
}


int Character::getInventorySize() const{
    return m_items.getSize();
}


Level* Character::getLevel() const{
    return m_level;
}

bool Character::getHuman() const{
    return m_Human;
}

bool Character::alive() const{
    return m_hitPoints > 0;
}

void Character::Attack(Character *e){
    e->Defense(this);
}

void Character::Defense(Character *e){
    m_hitPoints = m_hitPoints - e->getStrenght();
}































