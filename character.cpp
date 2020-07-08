#include "character.h"
#include "tile.h"
#include <ncurses.h>
#include "weapon.h"
#include "armor.h"

Character::Character(char icon, int strength, int stamina, bool isNPC) : icon(icon), strength(strength), stamina(stamina), NPC(isNPC)
{
    hp = getMaxHP();
    items = new List();
}

Character::~Character() {

    //delete all the item* in the list since delete list only deletes elements and not data in element struct
    List::iterator it = items->begin();
    List::iterator end = items->end();
    while(it != end) {
        delete *it; //delete data
        ++it;
    }
    delete items;
}

char Character::getIcon() const {
    return icon;
}

void Character::setTile(Tile *tile) {
    position = tile;
}

Tile* Character::getTile() {
    return position;
}

int Character::move() {
    return controller->move();
}

bool Character::isNPC() const
{
    return NPC;
}

bool Character::isAlive() const
{
    return alive;
}

void Character::takeDamage(int dmg)
{
    hp -= dmg;
}

int Character::getStrength() const
{
    return strength;
}

int Character::getStamina() const
{
    return stamina;
}

void Character::pickupItem(Item *item)
{
    items->push_back(item);
}

List* Character::getItems() const
{
    return items;
}

Controller *Character::getController() const
{
    return controller;
}

void Character::addMaxHp(int val)
{
    baseHP += val;
}

void Character::addCurrHp(int val)
{
    hp += val;
}

void Character::addStrength(int val)
{
    strength += val;
}

void Character::addStamina(int val)
{
    stamina += val;
}

void Character::setAlive(bool value)
{
    alive = value;
}

void Character::setController(Controller *ctrl) {
    controller = ctrl;
}

int Character::getMaxHP() const {
    return baseHP + stamina * 5;
}

int Character::getCurrentHP() const {
    return hp;
}
