#include "switch.h"
#include "logger.h"

//in the beginning its not pushed
Switch::Switch(int row, int col) : Tile('?', row, col)
{

}

Switch::~Switch()
{

}

void Switch::activate() {
    if(icon == '!') return;
    logging::Logger::instance()->log(logging::INFO, "Activated Switch at " + std::to_string(Tile::getRow()) + "-" + std::to_string(Tile::getCol()));
    for(Passive* p : Active::passives) {
        p->notify();
    }
    icon = '!';
}

Tile* Switch::onEnter(Tile *fromTile) {
    fight(fromTile->getCharacter(), Tile::getCharacter());
    logging::Logger::instance()->log(logging::INFO, "Left Tile" + std::to_string(fromTile->getRow()) + "-" + std::to_string(fromTile->getCol()) + " and moved to " +
                                       std::to_string(Tile::getRow()) + "-" + std::to_string(Tile::getCol()));
    if(Tile::getCharacter() != nullptr && Tile::getCharacter()->isAlive()) return nullptr;
    activate();
    return this;
}
