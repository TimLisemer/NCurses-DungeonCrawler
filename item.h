#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "character.h"
#include "tile.h"

class Character;
class Tile;

class Item
{
public:
    Item(const std::string &name);
    Item(const Item& i); // CC

    virtual ~Item();

    virtual void onEquip(Character* c);

    virtual void onDrop(Character* c, Tile* tile);

    virtual std::string getName() const;

private:
    std::string m_name;
};

#endif // ITEM_H
