#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"
#include "vector"
#include <list>

class Level
{
public:
    Level(); //creates a level by default!
    Level(int hoehe, int breite);
    Level(const Level &rhs) = delete;
    ~Level();

    Tile* getTile(int row, int col);

    const Tile *getTile(int row, int col) const;

    int getHoehe() const;

    int getBreite() const;

    void createNodes();

    std::list<int> getPath(Tile* from, Tile* to);

    void updateGraph(Tile* location);

    void placeCharacter(Character *c, int row, int col);

    void loadLevel(const string& lvl);

private:
    struct GraphNode {
        Tile* position;
        std::list<GraphNode*>* adjazenz_liste;
    };
    std::vector<GraphNode*> graph_nodes;
    int hoehe, breite;
    Tile*** welt;
    //vector saves all the controller so we dont lose there reference if character controller ist changed
    std::vector<Controller*> controller;
};

#endif // LEVEL_H
