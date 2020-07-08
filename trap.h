#ifndef TRAP_H
#define TRAP_H
#include "tile.h"

class Trap: public Tile
{
public:
    Trap(int row, int col);

    virtual ~Trap() override;

    virtual Tile* onEnter(Tile* fromTile) override;
};

#endif // TRAP_H
