#include "level.h"

#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <math.h>

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}

Level::Level(UserInterface* ui) {

    //Map Insert
    string LevelPath = "../Do12x-Team5MASTER-master/5-studi.map";
    ifstream file(LevelPath);
    if (!file.good()) {
        throw std::invalid_argument("Level File not found! --- Path = " + LevelPath);
    }
    vector<Node> nodes;
    while (true) {
        Node node;
        file >> node;
        nodes.push_back(node);
        if (file.eof())
        break;
    }

    //Load Map Information
    for (const auto &n : nodes) {
        if (n.name == "Map Information") {
            m_height = n.get<int>("rows");
            m_width = n.get<int>("cols");
        }
    }

    //create rows
    m_world = new Tile**[m_height];

    //create cols
    for(int i = 0; i < m_height; i++) {
        m_world[i] = new Tile*[m_width];
    }

    //create static elements
    for (size_t i = 0; i < nodes.size(); i++) {
        Node n = nodes.at(i);
        if (n.name == "Floor") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            m_world[row][col] = new Floor(row, col, this);
        }else if (n.name == "Wall") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            m_world[row][col] = new Wall(row, col, this);
        }else if (n.name == "Door") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            m_world[row][col] = new Door(row, col, this);
        }else if (n.name == "Trap") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            m_world[row][col] = new Trap(row, col, this, 5);
        }
    }

    //Create Dynamic Elements (Switch / Lever / Portal)
    for (size_t i = 0; i < nodes.size(); i++) {
        Node n = nodes.at(i);
        if (n.name == "Portal") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            int destrow = n.get<int>("destrow");
            int destcol = n.get<int>("destcol");
            m_world[row][col] = new Portal(row, col, destrow, destcol, this);
        }else if (n.name == "Switch") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            vector<int> destrows = n.get<vector<int>>("destrows");
            vector<int> destcols = n.get<vector<int>>("destcols");
            m_world[row][col] = new Switch(row, col, destrows, destcols, this);
        }else if (n.name == "Lever") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            vector<int> destrows = n.get<vector<int>>("destrows");
            vector<int> destcols = n.get<vector<int>>("destcols");
            m_world[row][col] = new Lever(row, col, destrows, destcols, this);

        //Items
        }else if (n.name == "Item") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            if(n.get<string>("type") == "Weapon"){
                m_world[row][col]->setItem(new Weapon(n.get<string>("name"), n.get<int>("strbonus")));
            }else if(n.get<string>("type") == "Armor"){
                m_world[row][col]->setItem(new Armor(n.get<string>("name"), n.get<int>("stabonus")));
            }else if(n.get<string>("type") == "Potion"){
                m_world[row][col]->setItem(new Potion(n.get<string>("name"), n.get<int>("amount"), n.get<int>("hp")));
            }else if(n.get<string>("type") == "Elixir"){
                m_world[row][col]->setItem(new Elixir(n.get<string>("name"), n.get<int>("amount"), n.get<int>("hp")));
            }
        }
    }


    //Load Characters
    m_characters = std::vector<Character*>();
    for (const auto &n : nodes) {
        if (n.name == "Character") {
            Character* c = nullptr;
            if(n.get<string>("controller") == "ConsoleController"){
                c = new Character(ui, this, n.get<char>("icon"), n.get<int>("strength"), n.get<int>("stamina"), true);
            }else if(n.get<string>("controller") == "StationaryController"){
                c = new Character(new StationaryController(), this, n.get<char>("icon"), n.get<int>("strength"), n.get<int>("stamina"), false);
            }else if(n.get<string>("controller") == "GuardController"){
                c = new Character(new GuardController(n.get<string>("pattern")), this, n.get<char>("icon"), n.get<int>("strength"), n.get<int>("stamina"), false);
            }else if(n.get<string>("controller") == "AttackController"){
                c = new Character(new AttackController(this), this, n.get<char>("icon"), n.get<int>("strength"), n.get<int>("stamina"), false);
            }
            placeCharacter(c, n.get<int>("row"), n.get<int>("col"));
        }
    }

}


//free allocated  space
Level::~Level() {
    //delete single tiles
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            delete m_world[i][j];
        }
        //delete single array
        delete[] m_world[i];
    }
    //delete array of arrays
    delete[] m_world;

    //delete all characters
    for(auto* c: m_characters){
        delete c;
    }
}

int Level::getHeight() const {
    return m_height;
}

int Level::getWidth() const {
    return m_width;
}

Tile* Level::getTile(const int row, const int col) {
    return m_world[row][col];
}

const Tile* Level::getTile(const int row, const int col) const {
    return m_world[row][col];
}

void Level::placeCharacter(Character *c, int row, int col) {
    m_world[row][col]->setCharacter(c);
    c->setTile(getTile(row, col));
    m_characters.push_back(c);
}

vector<Character*> Level::getCharacters() const{
    return m_characters;
}



void Level::createNodes()
{
    graph_nodes = std::vector<GraphNode*>();
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            //initial node creation without adjacency list
            graph_nodes.push_back(new GraphNode{m_world[i][j], nullptr});
        }
    }
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {

            updateGraph(m_world[i][j]);
            std::list<GraphNode*>* myList = new std::list<GraphNode*>();

            //check whether we can enter tile and if yes we push in adjacency list
            //add the graphNodes, we calculate the index in the vector

            if(j < m_width-1)                if(m_world[i][j+1]->clearPath()) myList->push_back(graph_nodes.at(m_width*i + j+1));
            if(j > 0)                       if(m_world[i][j-1]->clearPath()) myList->push_back(graph_nodes.at(m_width*i + j-1));
            if(i < m_height-1)                 if(m_world[i+1][j]->clearPath()) myList->push_back(graph_nodes.at(m_width*(i+1) + j));
            if(i > 0)                       if(m_world[i-1][j]->clearPath()) myList->push_back(graph_nodes.at(m_width*(i-1) + j));
            if(i < m_height-1 && j < m_width-1) if(m_world[i+1][j+1]->clearPath()) myList->push_back(graph_nodes.at(m_width*(i+1) + j+1));
            if(i > 0 && j < m_width-1)       if(m_world[i-1][j+1]->clearPath()) myList->push_back(graph_nodes.at(m_width*(i-1) + j+1));
            if(i < m_height-1 && j > 0)        if(m_world[i+1][j-1]->clearPath()) myList->push_back(graph_nodes.at(m_width*(i+1) + j-1));
            if(i > 0 && j > 0)              if(m_world[i-1][j-1]->clearPath()) myList->push_back(graph_nodes.at(m_width*(i-1) + j-1));

            //add list to Nodes
            graph_nodes.at(m_width * i + j)->adjazenz_liste = myList;
            //graph_nodes.at(i * m_width + j)->adjazenz_liste = myList;
        }
    }
}

std::list<int> Level::getPath(Tile* from, Tile* to)
{

    updateGraph(m_world[6][4]);


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
            if(abstand[row*m_width + col] < abstand[v->position->getRow()*breite + v->position->getCol()]) {
                //push old v again and pop new one from queue
                q.push(v);
                v = q.front();
                q.pop();
                continue; //so we dont push node again
            }
            q.push(q.front()); //enqueue back
            q.pop();
        }

        visited[v->position->getRow()*m_width + v->position->getCol()] = true;

        //aktualisiere Distanzen
        for(GraphNode* a : *v->adjazenz_liste) {
            size_t a_index = a->position->getRow()*m_width + a->position->getCol();
            size_t v_index = v->position->getRow()*m_width + v->position->getCol();
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

        if(visited[to->getRow() * m_width + to->getCol()]) {
            canBeReached = true;
            break; // reached goal
        }
    }

    if(!canBeReached) return std::list<int>('x'); //random char
    v = graph_nodes.at(to->getRow()*m_width + to->getCol());
    std::list<int> directions = std::list<int>();
    while(v->position != from) {
        //parse backwards from to-Tile to start
        //this means we need to invert the movements, e.g 8 (up from target) becomes 2 (down from attacker)
        size_t index = v->position->getRow() *m_width + v->position->getCol();
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


vector<Character*> Level::getHumanCharacters(){
    vector<Character*> returner;
    for(Character* c : m_characters){
        if(c->getHuman()){
              returner.push_back(c);
        }
    }
    return returner;
}

































