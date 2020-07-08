#ifndef PORTAL_H
#define PORTAL_H
#include "tile.h"

class Portal : public Tile
{
public:
    Portal(int row, int col, Tile* destination = nullptr);

    virtual ~Portal() override;

    void setDestination(Tile* dest);

    Tile* onEnter(Tile* fromTile) override;

private:
    Tile* destination; //default, set the destination with setter
};

#endif // PORTAL_H
