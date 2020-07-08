#ifndef TILE_H
#define TILE_H
#include <string>
#include "character.h"

using std::string;
class Item;
class Character;

class Tile
{
public:

    Tile(char icon, int row, int col);

    virtual ~Tile();

    char getIcon() const;

    int getRow() const;

    int getCol() const;

    const Tile* getDestination() const;

    bool hasCharacter() const;

    Character * getCharacter();

    void setCharacter(Character* character);

    virtual bool moveTo(Tile* destTile);

    virtual Tile* onEnter(Tile* fromTile) = 0;

    virtual Tile* onLeave(Tile* toTile);

    virtual bool canEnter();

    void setItem(Item *value);

    Item *getItem() const;

    void fight(Character* c1, Character* c2);
protected:
    char icon; // can be changed because of switch

private:
    const int row;
    const int col;
    Character* character;
    Item* item;

};

#endif // TILE_H
