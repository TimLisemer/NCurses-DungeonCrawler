#include "level.h"
#include "wall.h"
#include "portal.h"
#include "floor.h"
#include "door.h"
#include "switch.h"
#include "trap.h"
#include "lever.h"
#include "weapon.h"
#include "armor.h"
#include "potion.h"
#include "elixir.h"
#include "guardcontroller.h"
#include "stationarycontroller.h"
#include "consolecontroller.h"
#include "attackcontroller.h"

#include "node.h"

#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <math.h>

Level::Level() : hoehe(20), breite(20) {
    //create rows
    welt = new Tile**[hoehe];

    //create cols
    for(int i = 0; i < hoehe; i++) {
        welt[i] = new Tile*[breite];
    }

    //create elements, just a default level
    for(int i = 0; i < hoehe; i++) {
        for(int j = 0; j < breite; j++) {
            if(i == 1 && j == 8) {
                welt[i][j] = new Switch(i,j);
                continue;
            }
            if(i == 9 && j == 5) {
                welt[i][j] = new Door(i,j);
                continue;
            }
            if(i == 9) {
                welt[i][j] = new Wall(i, j);
                continue;
            }
            if(i == 5 && j == 5) {
                welt[i][j] = new Portal(i, j);
                continue;
            }
            if(i == 11 && j == 8) {
                welt[i][j] = new Portal(i, j);
                continue;
            }
            welt[i][j] = new Floor(i, j);
        }
    }
    dynamic_cast<Portal*>(welt[5][5])->setDestination(welt[11][8]);
    dynamic_cast<Portal*>(welt[11][8])->setDestination(welt[5][5]);
    dynamic_cast<Switch*>(welt[1][8])->attach(dynamic_cast<Door*>(welt[9][5]));
}

//free allocated  space
Level::~Level() {
    for(int i = 0; i < hoehe; i++) {
        for(int j = 0; j < breite; j++) {
            delete welt[i][j];
        }
        delete[] welt[i];
    }
    delete[] welt;
    for(Controller* c : controller) delete c;
    for(GraphNode* node : graph_nodes) delete node->adjazenz_liste;
}

Level::Level(int hoehe, int breite) : hoehe(hoehe), breite(breite) {
    //create rows
    welt = new Tile**[hoehe];

    //create cols
    for(int i = 0; i < hoehe; i++) {
        welt[i] = new Tile*[breite];
    }
}

Tile* Level::getTile(int row, int col) {
    return welt[row][col];
}

int Level::getHoehe() const {
    return hoehe;
}

int Level::getBreite() const {
    return breite;
}

void Level::createNodes()
{
    graph_nodes = std::vector<GraphNode*>();
    for(int i = 0; i < hoehe; i++) {
        for(int j = 0; j < breite; j++) {
            //initial node creation without adjacency list
            graph_nodes.push_back(new GraphNode{welt[i][j], nullptr});
        }
    }
    for(int i = 0; i < hoehe; i++) {
        for(int j = 0; j < breite; j++) {

            updateGraph(welt[i][j]);
            std::list<GraphNode*>* myList = new std::list<GraphNode*>();

            //check whether we can enter tile and if yes we push in adjacency list
            //add the graphNodes, we calculate the index in the vector

            if(j < breite-1)                if(welt[i][j+1]->canEnter()) myList->push_back(graph_nodes.at(breite*i + j+1));
            if(j > 0)                       if(welt[i][j-1]->canEnter()) myList->push_back(graph_nodes.at(breite*i + j-1));
            if(i < hoehe-1)                 if(welt[i+1][j]->canEnter()) myList->push_back(graph_nodes.at(breite*(i+1) + j));
            if(i > 0)                       if(welt[i-1][j]->canEnter()) myList->push_back(graph_nodes.at(breite*(i-1) + j));
            if(i < hoehe-1 && j < breite-1) if(welt[i+1][j+1]->canEnter()) myList->push_back(graph_nodes.at(breite*(i+1) + j+1));
            if(i > 0 && j < breite-1)       if(welt[i-1][j+1]->canEnter()) myList->push_back(graph_nodes.at(breite*(i-1) + j+1));
            if(i < hoehe-1 && j > 0)        if(welt[i+1][j-1]->canEnter()) myList->push_back(graph_nodes.at(breite*(i+1) + j-1));
            if(i > 0 && j > 0)              if(welt[i-1][j-1]->canEnter()) myList->push_back(graph_nodes.at(breite*(i-1) + j-1));

            //add list to Node
            graph_nodes.at(i*breite+j)->adjazenz_liste = myList;
        }
    }
}

std::list<int> Level::getPath(Tile* from, Tile* to)
{

    updateGraph(welt[6][4]);


    //trying to implement dijkstra
    //still missing: update after door opens in createNodes
    std::vector<double> abstand(graph_nodes.size(),-1.0); //init with -1; counts as infinite
    std::vector<GraphNode*> previous(graph_nodes.size(), nullptr); //previous is unknown
    std::vector<bool> visited(graph_nodes.size(), false); // no nodes visited

    GraphNode* v;
    for(size_t i = 0; i < graph_nodes.size(); i++) {
        if(graph_nodes.at(i)->position == from) {
            v = graph_nodes.at(i);
            abstand.at(i) = 0; //abstand from = 0;
        }
    }
    std::queue<GraphNode*> q;
    q.push(v); //init queue

    bool canBeReached = false; //is there a possible way?
    while(!q.empty()) {
        //search smallest dist
        v = q.front();
        q.pop();
        for(size_t i = 0; i < q.size(); i++) {
            size_t row = q.front()->position->getRow();
            size_t col = q.front()->position->getCol();
            if(abstand[row*breite + col] < abstand[v->position->getRow()*breite + v->position->getCol()]) {
                //push old v again and pop new one from queue
                q.push(v);
                v = q.front();
                q.pop();
                continue; //so we dont push node again
            }
            q.push(q.front()); //enqueue back
            q.pop();
        }

        visited[v->position->getRow()*breite + v->position->getCol()] = true;

        //aktualisiere Distanzen
        for(GraphNode* a : *v->adjazenz_liste) {
            size_t a_index = a->position->getRow()*breite + a->position->getCol();
            size_t v_index = v->position->getRow()*breite + v->position->getCol();
            if(visited[a_index]) continue; //already done
            if(abstand[a_index] < 0.0) q.push(a); // add new node if not yet in queue, so if dist = infinite

            //if new dist is smaller update
            //looks ugly but essentially just checks if the route over node of v_index is shorter
            //if node has negative distance, its not yet found so we just set it
            if((abstand[a_index] >= 0.0 && abstand[a_index] >
                    abstand[v_index] + std::sqrt(abs(v->position->getRow() - a->position->getRow()) + abs(v->position->getCol() - a->position->getCol())))
                    || abstand[a_index] < 0.0)
            {
                abstand[a_index] = abstand[v_index] + std::sqrt(abs(v->position->getRow() - a->position->getRow()) + abs(v->position->getCol() - a->position->getCol()));
                previous[a_index] = v;
            }
        }

        if(visited[to->getRow() * breite + to->getCol()]) {
            canBeReached = true;
            break; // reached goal
        }
    }

    if(!canBeReached) return std::list<int>('x'); //random char
    v = graph_nodes.at(to->getRow()*breite + to->getCol());
    std::list<int> directions = std::list<int>();
    while(v->position != from) {
        //parse backwards from to-Tile to start
        //this means we need to invert the movements, e.g 8 (up from target) becomes 2 (down from attacker)
        size_t index = v->position->getRow() *breite + v->position->getCol();
        GraphNode* prev = previous[index];

        int rowDiff = v->position->getRow() - prev->position->getRow();
        int colDiff = v->position->getCol() - prev->position->getCol();
        int dir;

        if(rowDiff == 0 && colDiff == 0) dir = '5';
        if(rowDiff == 0 && colDiff == 1) dir = '6';
        if(rowDiff == 0 && colDiff == -1) dir = '4';
        if(rowDiff == 1 && colDiff == 0) dir = '2';
        if(rowDiff == 1 && colDiff == 1) dir = '3';
        if(rowDiff == 1 && colDiff == -1) dir = '1';
        if(rowDiff == -1 && colDiff == 0) dir = '8';
        if(rowDiff == -1 && colDiff == 1) dir = '9';
        if(rowDiff == -1 && colDiff == -1) dir = '7';

        directions.push_front(dir);

        v = previous[index];
    }

    return directions;
}

void Level::updateGraph(Tile *location)
{
    //TODO update tiles around location and maybe add to adjacency list, just for static Tiles, not for characters which can move around
    //this could be done with another function to which we give the prev and curr tiles
    // 0 0 0    this function starts at top left and updates the adjacency lists
    // 0 X 0
    // 0 0 0
    for(int i = location->getRow()-1; i < location->getRow()+2; i++) {
        for(int j = location->getCol(); j < location->getCol()+2; j++) {
            if(i < 0 || i < 0) continue; //sanity check
/**            std::list<GraphNode*>* myList = new std::list<GraphNode*>();

            //check whether we can enter tile and if yes we push in adjacency list
            //add the graphNodes, we calculate the index in the vector

            if(j < breite-1)                if(welt[i][j+1]->canEnter()) myList->push_back(graph_nodes.at(breite*i + j+1));
            if(j > 0)                       if(welt[i][j-1]->canEnter()) myList->push_back(graph_nodes.at(breite*i + j-1));
            if(i < hoehe-1)                 if(welt[i+1][j]->canEnter()) myList->push_back(graph_nodes.at(breite*(i+1) + j));
            if(i > 0)                       if(welt[i-1][j]->canEnter()) myList->push_back(graph_nodes.at(breite*(i-1) + j));
            if(i < hoehe-1 && j < breite-1) if(welt[i+1][j+1]->canEnter()) myList->push_back(graph_nodes.at(breite*(i+1) + j+1));
            if(i > 0 && j < breite-1)       if(welt[i-1][j+1]->canEnter()) myList->push_back(graph_nodes.at(breite*(i-1) + j+1));
            if(i < hoehe-1 && j > 0)        if(welt[i+1][j-1]->canEnter()) myList->push_back(graph_nodes.at(breite*(i+1) + j-1));
            if(i > 0 && j > 0)              if(welt[i-1][j-1]->canEnter()) myList->push_back(graph_nodes.at(breite*(i-1) + j-1));

            //add list to Node
            graph_nodes.at(i*breite+j)->adjazenz_liste = myList; */
        }
    }
}

const Tile* Level::getTile(int row, int col) const {
    return welt[row][col];
}

void Level::placeCharacter(Character *c, int row, int col) {
    welt[row][col]->setCharacter(c);
    c->setTile(welt[row][col]);
}


void Level::loadLevel(const string &lvl) {
     std::ifstream file(lvl);
     if(!file.good()) {
         throw std::invalid_argument("file cannot be loaded");
     }

    std::vector<Node> nodes;
    while(!file.eof()) {
        Node n;
        //uses overloaded opearator>>(istream, Node);
        file >> n;
        nodes.push_back(n);
    }

    //free memory
    for(int i = 0; i < hoehe; i++) {
        for(int j = 0; j < breite; j++) {
            delete welt[i][j];
        }
        delete[] welt[i];
    }
    delete[] welt;
    for(Controller* c : controller) delete c;
    for(GraphNode* node : graph_nodes) delete node->adjazenz_liste;

    if(nodes.at(0).name == "Map Information") {
        hoehe = nodes.at(0).get<int>("rows");
        breite = nodes.at(0).get<int>("cols");

        welt = new Tile**[hoehe];
        for(int i = 0; i < hoehe; i++) {
            welt[i] = new Tile*[breite];
        }
    }


    //extract data
    for(const Node& n : nodes) {
        Tile* t = nullptr;
        //allocate new memory
        if(n.name == "Floor") {
            t = new Floor(n.get<int>("row"), n.get<int>("col"));
        }
        else if(n.name == "Portal") {
            t = new Portal(n.get<int>("row"), n.get<int>("col"));
        }
        else if(n.name == "Wall") {
            t = new Wall(n.get<int>("row"), n.get<int>("col"));
        }
        else if(n.name == "Door") {
            t = new Door(n.get<int>("row"), n.get<int>("col"));
        }
        else if(n.name == "Switch") {
            t = new Switch(n.get<int>("row"), n.get<int>("col"));
        }
        else if(n.name == "Trap") {
            t = new Trap(n.get<int>("row"), n.get<int>("col"));
        }
        else if(n.name == "Lever") {
            t = new Lever(n.get<int>("row"), n.get<int>("col"));
        }

        if(t) welt[t->getRow()][t->getCol()] = t;
    }

    //go through again to set destination and other stuff that requires initialisation
    for(const Node& n : nodes) {
        if(n.name == "Portal") {
            dynamic_cast<Portal*>(welt[n.get<int>("row")][n.get<int>("col")])->setDestination(welt[n.get<int>("destrow")][n.get<int>("destcol")]);
        }
        else if(n.name == "Character") {
            //strength and stamina are not given yet?
            Character* c = nullptr;
            if(n.get<string>("controller") == "GuardController") {
                c = new Character(n.get<char>("icon"),n.get<int>("strength"),n.get<int>("stamina"));
                Controller* con = new GuardController(n.get<string>("pattern"));
                c->setController(con);
                controller.push_back(con);
            } else if (n.get<string>("controller") == "StationaryController") {
                c = new Character(n.get<char>("icon"),n.get<int>("strength"),n.get<int>("stamina"));
                Controller* con = new StationaryController();
                c->setController(con);
                controller.push_back(con);
            } else if (n.get<string>("controller") == "ConsoleController") {
                c = new Character(n.get<char>("icon"),n.get<int>("strength"),n.get<int>("stamina"), false);
                Controller* con = new ConsoleController();
                c->setController(con);
                controller.push_back(con);
            } else if(n.get<string>("controller") == "AttackController") {
                c = new Character(n.get<char>("icon"),n.get<int>("strength"),n.get<int>("stamina"));
                Controller* con = new AttackController(this, c);
                c->setController(con);
                controller.push_back(con);
            }
            if(c) placeCharacter(c, n.get<int>("row"), n.get<int>("col"));
        }
        else if (n.name == "Switch" || n.name == "Lever") {
            string cols = n.get<string>("destcols");
            string rows = n.get<string>("destrows");
            std::vector<int> colsInt;
            std::vector<int> rowsInt;

            std::stringstream sCols(cols);
            std::stringstream sRows(rows);

            //parse out the values
            int val;
            while(sCols >> val) colsInt.push_back(val);
            while(sRows >> val) rowsInt.push_back(val);

            //combined switch and Level in one loop since they do essentially the same thing and they are both active objects
            for(unsigned int i = 0; i < rowsInt.size() && i < colsInt.size(); i++) {
                dynamic_cast<Active*>(welt[n.get<int>("row")][n.get<int>("col")])
                        ->attach(dynamic_cast<Passive*>(welt[rowsInt.at(i)][colsInt.at(i)]));
            }
        }
        else if (n.name == "Item") {
            if(n.get<string>("type") == "Weapon") {
                welt[n.get<int>("row")][n.get<int>("col")]->setItem(new Weapon(n.get<string>("name"), n.get<int>("strbonus")));
            } else if(n.get<string>("type") == "Armor") {
                welt[n.get<int>("row")][n.get<int>("col")]->setItem(new Armor(n.get<string>("name"), n.get<int>("stabonus")));
            } else if(n.get<string>("type") == "Potion") {
                welt[n.get<int>("row")][n.get<int>("col")]->setItem(new Potion(n.get<string>("name"), n.get<int>("amount"), n.get<int>("hp")));
            } else if(n.get<string>("type") == "Elixir") {
                welt[n.get<int>("row")][n.get<int>("col")]->setItem(new Elixir(n.get<string>("name"), n.get<int>("amount"), n.get<int>("hp")));
            }
        }
    }
    createNodes();
}
