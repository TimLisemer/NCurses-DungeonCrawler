#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"
#include <fstream>
#include <vector>
#include <list>
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
    Level(int width, int height);
    Level(const Level &rhs) = delete;
    ~Level();

    Tile* getTile(const int row, const int col);

    void createNodes();

    std::list<int> getPath(Tile* from, Tile* to);

    const Tile *getTile(const int row, const int col) const;

    void updateGraph(Tile* location);

    int getHeight() const;
    int getWidth() const;
    void placeCharacter(Character *c, int row, int col);

    vector<Character*> getHumanCharacters();

    vector<Character*> getCharacters() const;

private:
    struct GraphNode{
        Tile* position;
        std::list<GraphNode*> adjazenz_liste;
    };
    std::vector<GraphNode*> graph_nodes;
    int m_height, m_width;
    std::vector<Character*> m_characters;
    Tile*** m_world;
};

#endif // LEVEL_H
