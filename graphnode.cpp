#include "graphnode.h"

GraphNode::GraphNode(){}


GraphNode::GraphNode(Tile* p) :  position(p) {}

GraphNode::~GraphNode(){
    delete adjazenz_list;
}
