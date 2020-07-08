#ifndef WALL_H
#define WALL_H
#include "tile.h"


class Wall : public Tile
{
public:
    Wall(int row, int col);

    virtual ~Wall() override;

    virtual bool canEnter() override;

    virtual Tile* onEnter(Tile *fromTile) override;
};

#endif // WALL_H
