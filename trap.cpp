#include "trap.h"

Trap::Trap(int row, int col) : Tile('.',row,col)
{

}

Trap::~Trap()
{

}

Tile *Trap::onEnter(Tile *fromTile)
{
    fight(fromTile->getCharacter(), Tile::getCharacter());
    if(Tile::getCharacter() != nullptr && Tile::getCharacter()->isAlive()) return nullptr;

    if(icon != 'T') {
        icon = 'T';
        fromTile->getCharacter()->takeDamage(20);
    }
    return this;
}
