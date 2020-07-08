#include "wall.h"
#include "logger.h"
Wall::Wall(int row, int col) : Tile('#', row, col)
{

}

Wall::~Wall() {

}

bool Wall::canEnter()
{
    return false; //cant be entered
}

Tile* Wall::onEnter(Tile* fromTile) {
    logging::Logger::instance()->log(logging::INFO, "Left Tile" + std::to_string(fromTile->getRow()) + "-" + std::to_string(fromTile->getCol()) + " and moved to " +
                                       std::to_string(Tile::getRow()) + "-" + std::to_string(Tile::getCol()));
    return nullptr;
}
