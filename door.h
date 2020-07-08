#ifndef DOOR_H
#define DOOR_H
#include "passive.h"
#include "tile.h"

class Door : public Tile, public Passive
{
public:
    Door(int row, int col);

    virtual ~Door() override;

    virtual void notify() override;

    virtual bool canEnter() override;

    virtual Tile* onEnter(Tile* fromTile) override;
};

#endif // DOOR_H
