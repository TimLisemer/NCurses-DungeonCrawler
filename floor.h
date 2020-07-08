#ifndef FLOOR_H
#define FLOOR_H
#include "tile.h"

class Floor : public Tile
{
public:
    Floor(int row, int col);
    virtual ~Floor() override;

    Tile* onEnter(Tile* fromTile) override;
};

#endif // FLOOR_H
