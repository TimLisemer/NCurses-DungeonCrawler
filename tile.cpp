

#include "tile.h"
#include "character.h"
#include "logger.h"

Tile::Tile(char icon, int row, int col)
    :  icon(icon), row(row), col(col)
{
    character = nullptr;
    item = nullptr;
}

Tile::~Tile() {
    delete item;
}

char Tile::getIcon() const {
    if(character != nullptr && character->isAlive()) {
        return character->getIcon();
    }
    if(item != nullptr) {
        return '*';
    }
    return icon;
}

int Tile::getRow() const {
    return row;
}

Character* Tile::getCharacter() {
    return character;
}

int Tile::getCol() const {
    return col;
}

bool Tile::hasCharacter() const {
    return character;
}

void Tile::setCharacter(Character *character) {
    this->character = character;
}

bool Tile::moveTo(Tile *destTile) {
    //trueDest because of tp
    Tile* trueDest = destTile->onEnter(this);
    if(!onLeave(destTile) || !trueDest) {
        return false;
    }

    //does the destination have an item? if yes pick it up
    if(trueDest->getItem() != nullptr) {
        character->pickupItem(trueDest->getItem());
        trueDest->getItem()->onEquip(character);
        trueDest->setItem(nullptr);
    }

    //update info
    character->setTile(trueDest);
    trueDest->setCharacter(character);
    character = nullptr;

    return true;
}

Tile* Tile::onLeave(Tile *toTile) {
    //für fail noch keinen anwendungsfall, if nur für warning
    if(toTile) { }
    return this;
}

bool Tile::canEnter()
{
    //this function is for creating the graph, but onEnter might have some unwanted side effects,
    //so this function just checks if this Tile has no character and can be entered
    if(character == nullptr) return true;
    return false;
}

void Tile::setItem(Item *value)
{
    item = value;
}

Item *Tile::getItem() const
{
    return item;
}

void Tile::fight(Character *c1, Character *c2)
{
    if((!c1 || !c2) || (c1->isNPC() && c2->isNPC()) || (!c1->isNPC() && !c2->isNPC())) return;
    c2->takeDamage(c1->getStrength());
    if(c2->getCurrentHP() > 0) {
        c1->takeDamage(c2->getStrength());
    } else {
        c2->setAlive(false);
    }
}
