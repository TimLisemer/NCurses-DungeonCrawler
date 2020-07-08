#include "lever.h"

Lever::Lever(int row, int col) : Tile('L',row, col)
{

}

Lever::~Lever()
{

}

void Lever::activate()
{
    for(Passive* p : passives) {
        p->notify();
    }
}

Tile* Lever::onEnter(Tile *from) {
    fight(from->getCharacter(), Tile::getCharacter());
    if(Tile::getCharacter() != nullptr && Tile::getCharacter()->isAlive()) return nullptr;
    activate();
    return this;
}
