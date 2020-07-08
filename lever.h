#ifndef LEVER_H
#define LEVER_H
#include "tile.h"
#include "active.h"


class Lever : public Tile, public Active
{
public:
    Lever(int row, int col);

    virtual ~Lever() override;

    virtual void activate() override;

    virtual Tile* onEnter(Tile* fromTile ) override;
};

#endif // LEVER_H
