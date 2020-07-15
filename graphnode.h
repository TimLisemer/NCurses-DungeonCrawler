#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "tile.h"

class Tile;

class GraphNode
{
public:
    GraphNode();
    GraphNode(Tile* p);
    ~GraphNode();
    Tile* position;
    double distance = -1.0;
    int direction = 0;
    GraphNode* previous = nullptr;
    std::vector<GraphNode*>* adjazenz_list;
    std::vector<double>* adjazenz_distance;  //sowas wie ne java hashmap wäre hier besser aber keine lust zu schauen obts das in c++ gibt
    std::vector<int>* adjazenz_direction;
};

#endif // GRAPHNODE_H
