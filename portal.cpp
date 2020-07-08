#include "portal.h"
#include "logger.h"

Portal::Portal(int row, int col, Tile* destination) : Tile('O', row, col), destination(destination)
{

}

Portal::~Portal() {

}

void Portal::setDestination(Tile *dest) {
    destination = dest;
}

Tile* Portal::onEnter(Tile* fromTile) {
    logging::Logger::instance()->log(logging::INFO, "Left Tile" + std::to_string(fromTile->getRow()) + "-" + std::to_string(fromTile->getCol()) + " and moved to " +
                                       std::to_string(Tile::getRow()) + "-" + std::to_string(Tile::getCol()));
    fight(fromTile->getCharacter(), Tile::getCharacter());
    if(destination->getCharacter() != nullptr && Tile::getCharacter()->isAlive()) return nullptr;
    return destination;
}
