#ifndef SWITCH_H
#define SWITCH_H
#include "active.h"
#include "tile.h"

class Switch : public Tile, public Active
{
public:
    Switch(int row, int col);

    virtual ~Switch() override;

    virtual void activate() override;

    virtual Tile* onEnter(Tile* fromTile) override;
};

#endif // SWITCH_H
