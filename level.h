#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"


class Level
{
public:
    Level();
    Level(int m_height, int m_width);
    Level(const Level &rhs) = delete;

    ~Level();


    Tile* getTile(int row, int col);

    const Tile *getTile(int row, int col) const;

    int getHeight() const;

    int getWidth() const;

    void placeCharacter(Character *c, int row, int col);

private:
    const int m_height, m_width;
    Tile*** m_world;
};

#endif // LEVEL_H
