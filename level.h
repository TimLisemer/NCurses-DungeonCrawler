#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"
#include <fstream>
#include "node.h"

using std::ifstream;

class Tile;
class Character;

class Level {

public:
    Level();
    Level(const int m_height, const int m_width);
    Level(const Level &rhs) = delete;

    ~Level();


    Tile* getTile(const int row, const int col);

    const Tile *getTile(const int row, const int col) const;

    int getHeight() const;
    int getWidth() const;

    Tile*** getWorld() const;

    void placeCharacter(Character *c, const int row, const int col);

private:
    int m_height, m_width;
    Tile*** m_world;
};

#endif // LEVEL_H
