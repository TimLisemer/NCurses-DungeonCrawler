#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"
#include <fstream>

#include "node.h"
#include "userinterface.h"
#include "tile.h"
#include "character.h"

using std::string;
using std::ifstream;


class UserInterface;
class Tile;
class Character;

class Level {

public:

    Level(UserInterface* ui);
    Level(const Level &rhs) = delete;
    ~Level();

    Tile* getTile(const int row, const int col);

    const Tile *getTile(const int row, const int col) const;

    int getHeight() const;
    int getWidth() const;
    void placeCharacter(Character *c, int row, int col);

    vector<Tile*> getPath(Tile* from, Tile* to);
    Character* getHumanCharacter();

    std::vector<Character*> getCharacters() const;

private:
    int m_height, m_width;
    std::vector<Character*> m_characters;
    Tile*** m_world;
};

#endif // LEVEL_H
