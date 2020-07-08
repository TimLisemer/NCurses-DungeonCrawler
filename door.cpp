#include "door.h"
#include "logger.h"

Door::Door(int row, int col) : Tile('X', row, col)
{

}

Door::~Door()
{

}

void Door::notify() {
    logging::Logger::instance()->log(logging::INFO, "Notified door at" + std::to_string(Tile::getRow()) + "-" + std::to_string(Tile::getCol()));
    if(icon == 'X')  {
        icon = '\\';
        return; //switch and return
    }
    if(icon == '\\') icon = 'X';
}

bool Door::canEnter()
{
    if(Tile::canEnter() && icon == '\\') return true;
    return false;
}

Tile* Door::onEnter(Tile *fromTile) {
    //if door has been opened
    logging::Logger::instance()->log(logging::INFO, "Left Tile" + std::to_string(fromTile->getRow()) + "-" + std::to_string(fromTile->getCol()) + " and moved to " +
                                     std::to_string(Tile::getRow()) + "-" + std::to_string(Tile::getCol()));

    fight(fromTile->getCharacter(), Tile::getCharacter());
    if (icon == '\\' && Tile::getCharacter() == nullptr) {
        return this;
    } else if(Tile::getCharacter() != nullptr) {
        if(!Tile::getCharacter()->isAlive()) return this;
    }
    return nullptr;
}
