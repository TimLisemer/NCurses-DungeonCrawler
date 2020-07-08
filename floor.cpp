#include "floor.h"
#include "logger.h"

Floor::Floor(int row, int col) : Tile('.',row,col)
{

}

Floor::~Floor() {

}

Tile* Floor::onEnter(Tile *fromTile) {
    logging::Logger::instance()->log(logging::INFO, "Left Tile" + std::to_string(fromTile->getRow()) + "-" + std::to_string(fromTile->getCol()) + " and moved to " +
                                       std::to_string(Tile::getRow()) + "-" + std::to_string(Tile::getCol()));
    fight(fromTile->getCharacter(), Tile::getCharacter());
    if(Tile::getCharacter() != nullptr && Tile::getCharacter()->isAlive()) return nullptr;
    return this;
}
