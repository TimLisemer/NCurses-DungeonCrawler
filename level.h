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

using std::string;
using std::ifstream;


class UserInterface;
class Tile;
class Character;
class GraphNode;
class Portal;

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

    std::list<int> getPath(Tile* from, Tile* to);
    void createNodes();
    void updateGraph();

    Portal* isPortal(Tile* t);
    vector<Tile*> getNeighbours(Tile* t);

    vector<Character*> getHumanCharacters();

    vector<Character*> getCharacters() const;


private:

    struct GraphNode{
        Tile* position;
        double distance = -1.0;
        int direction = 0;
        GraphNode* previous = nullptr;

        std::vector<GraphNode*>* adjazenz_nodes;
        std::vector<double>* adjazenz_distance;
        std::vector<int>* adjazenz_direction;
    };

    std::vector<GraphNode*> graph_nodes;

    int m_height, m_width;
    std::vector<Character*> m_characters;
    Tile*** m_world;
};

#endif // LEVEL_H
