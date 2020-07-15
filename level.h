#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"
#include <fstream>
#include <list>

#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <math.h>

#include "node.h"
#include "userinterface.h"
#include "tile.h"
#include "character.h"
#include "graphnode.h"

using std::string;
using std::ifstream;


class UserInterface;
class Tile;
class Character;
class GraphNode;

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

    std::list<Tile*> getPath(Tile* from, Tile* to);
    void createNodes();
    void updateGraph();


    vector<Character*> getHumanCharacters();

    vector<Character*> getCharacters() const;


private:
    std::vector<GraphNode*> graph_nodes;

    int m_height, m_width;
    std::vector<Character*> m_characters;
    Tile*** m_world;
};

#endif // LEVEL_H
