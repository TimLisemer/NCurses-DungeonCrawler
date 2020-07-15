#include "level.h"

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}

Level::Level(UserInterface* ui) {

    //Map Insert
    string LevelPath = "../Ncurses-DungeonCrawler-master/5-studi.map";
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

    createNodes();

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
    for(GraphNode* node : graph_nodes){
        delete node->adjazenz_list;
        delete node;
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



std::list<int> Level::getPath(Tile* from, Tile* to){

    GraphNode* toNode = graph_nodes.at(to->getRow() * m_width + to->getCol());
    GraphNode* fromNode = graph_nodes.at(from->getRow() * m_width + from->getCol());
    fromNode->distance = 0;

    GraphNode* checkNode = fromNode;
    vector<vector<GraphNode*>>* distantNodes = new vector<vector<GraphNode*>>{};
    vector<vector<GraphNode*>> newDistantNodes;

    while(true){

        //remove checkNode from shortestDistanceNodes to avoid loop
        newDistantNodes = vector<vector<GraphNode*>>{};
        for(size_t i = 0; i < distantNodes->size(); i++){
            for(size_t d = 0; d < distantNodes->at(i).size(); d++){
                if(distantNodes->at(i).at(d) != checkNode){
                    if(newDistantNodes.size() > i){
                        newDistantNodes.at(i).push_back(distantNodes->at(i).at(d));
                    }else{
                        newDistantNodes.push_back(vector<GraphNode*>{distantNodes->at(i).at(d)});
                    }
                }
            }
        }
        distantNodes->clear();
        for(size_t i = 0; i < newDistantNodes.size(); i++){
            for(size_t d = 0; d < newDistantNodes.at(i).size(); d++){
                if(newDistantNodes.at(i).at(d) != checkNode){
                    if(distantNodes->size() > i){
                        distantNodes->at(i).push_back(newDistantNodes.at(i).at(d));
                    }else{
                        distantNodes->push_back(vector<GraphNode*>{newDistantNodes.at(i).at(d)});
                    }
                }
            }
        }

        //Djikstra attempt
        GraphNode* nextCheckNode = nullptr;

        vector<GraphNode*>* checkList = checkNode->adjazenz_list;
        vector<double>* checkDistance = checkNode->adjazenz_distance;
        for(size_t i = 0; i < checkList->size(); i++){
            if((checkList->at(i)->distance == -1 || checkList->at(i)->distance > checkNode->distance+checkDistance->at(i)) && checkList->at(i) != checkNode && checkList->at(i) != checkList->at(i)->previous){
                checkList->at(i)->distance = checkNode->distance+checkDistance->at(i);
                checkList->at(i)->previous = checkNode;
                checkList->at(i)->direction = checkNode->adjazenz_direction->at(i);

                if(distantNodes->size() >= checkList->at(i)->distance){
                    distantNodes->at((int) checkList->at(i)->distance - 1).push_back(checkList->at(i));
                }else{
                    distantNodes->push_back(vector<GraphNode*>{checkList->at(i)});
                }


                if(checkList->at(i)->distance <= distantNodes->at(0).at(0)->distance){
                    nextCheckNode = checkList->at(i);
                }
            }
        }

        if(nextCheckNode != nullptr){
            checkNode = nextCheckNode;
        }else if(distantNodes->size() == 0){
            if(checkNode == toNode){
                break;
            }else{
                if(toNode->previous == nullptr){
                    //No Path
                    return std::list<int>{'5'};
                }else{
                    break;
                }
            }
        }else{
            checkNode = distantNodes->at(0).at(0);
        }

    }

    std::list<int> path;
    GraphNode* nextNode = toNode;
    while(nextNode != fromNode){
        path.push_front(nextNode->direction);
        nextNode = nextNode->previous;
    }

    return path;

}


//Todo: updateGraph funktion zum laufen bekommen
void Level::updateGraph(){
    for(int i = 0; i < m_height; i++) {
        for(int d = 0; d < m_width; d++) {

            graph_nodes.at(i * m_width + d)->distance = -1;
            graph_nodes.at(i * m_width + d)->previous = nullptr;
            graph_nodes.at(i * m_width + d)->direction = 0;

            std::vector<GraphNode*>* nL = new std::vector<GraphNode*>();    //nodeList
            std::vector<double>* dL = new std::vector<double>();            //distanceList
            std::vector<int>* dD = new std::vector<int>();                  //distantDirection


            //check whether we can enter tile and if yes we push in adjacency list
            //add the graphNodes, we calculate the index in the vector

            if(i < m_height-1 && d < m_width-1){    int index = (i+1) * m_width + d+1;  if(m_world[i+1][d+1]->clearPath()){ nL->push_back(graph_nodes.at(index)); dL->push_back(1.1); dD->push_back('3');}}
            if(i > 0 && d < m_width-1){             int index = (i-1) * m_width + d+1;  if(m_world[i-1][d+1]->clearPath()){ nL->push_back(graph_nodes.at(index)); dL->push_back(1.1); dD->push_back('9');}}
            if(i < m_height-1 && d > 0){            int index = (i+1) * m_width + d-1;  if(m_world[i+1][d-1]->clearPath()){ nL->push_back(graph_nodes.at(index)); dL->push_back(1.1); dD->push_back('1');}}
            if(i > 0 && d > 0){                     int index = (i-1) * m_width + d-1;  if(m_world[i-1][d-1]->clearPath()){ nL->push_back(graph_nodes.at(index)); dL->push_back(1.1); dD->push_back('7');}}
            if(d != m_width-1){                      int index = i * m_width + d+1;      if(m_world[i][d+1]->clearPath()){ nL->push_back(graph_nodes.at(index)); dL->push_back(1); dD->push_back('6');}}
            if(d != 0){                              int index = i * m_width + d-1;      if(m_world[i][d-1]->clearPath()){ nL->push_back(graph_nodes.at(index)); dL->push_back(1); dD->push_back('4');}}
            if(i != m_height-1){                     int index = (i+1) * m_width + d;    if(m_world[i+1][d]->clearPath()){ nL->push_back(graph_nodes.at(index)); dL->push_back(1); dD->push_back('2');}}
            if(i != 0){                              int index = (i-1) * m_width + d;    if(m_world[i-1][d]->clearPath()){ nL->push_back(graph_nodes.at(index)); dL->push_back(1); dD->push_back('8');}}

            //add list to Nodes
            graph_nodes.at(i * m_width + d)->adjazenz_list = nL;
            graph_nodes.at(i * m_width + d)->adjazenz_distance = dL;
            graph_nodes.at(i * m_width + d)->adjazenz_direction = dD;
        }
    }
}



void Level::createNodes(){

    graph_nodes = std::vector<GraphNode*>();
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            //initial node creation without adjacency list
            graph_nodes.push_back(new GraphNode(m_world[i][j]));
        }
    }

    for(int i = 0; i < m_height; i++) {
        for(int d = 0; d < m_width; d++) {

            std::vector<GraphNode*>* nL = new std::vector<GraphNode*>();    //nodeList
            std::vector<double>* dL = new std::vector<double>();            //distanceList
            std::vector<int>* dD = new std::vector<int>();                  //distantDirection


            //check whether we can enter tile and if yes we push in adjacency list
            //add the graphNodes, we calculate the index in the vector

            int in; Tile* t;

            if(i < m_height-1 && d < m_width-1){    in = (i+1) * m_width + d+1;  t = m_world[i+1][d+1];   Portal* p = isPortal(t); if(p != nullptr){t=p->getDestination(); in = t->getRow()*m_width+t->getCol();} if(t->clearPath()){ nL->push_back(graph_nodes.at(in)); dL->push_back(1.1); dD->push_back('3');}}
            if(i > 0 && d < m_width-1){             in = (i-1) * m_width + d+1;  t = m_world[i-1][d+1];   Portal* p = isPortal(t); if(p != nullptr){t=p->getDestination(); in = t->getRow()*m_width+t->getCol();} if(t->clearPath()){ nL->push_back(graph_nodes.at(in)); dL->push_back(1.1); dD->push_back('9');}}
            if(i < m_height-1 && d > 0){            in = (i+1) * m_width + d-1;  t = m_world[i+1][d-1];   Portal* p = isPortal(t); if(p != nullptr){t=p->getDestination(); in = t->getRow()*m_width+t->getCol();} if(t->clearPath()){ nL->push_back(graph_nodes.at(in)); dL->push_back(1.1); dD->push_back('1');}}
            if(i > 0 && d > 0){                     in = (i-1) * m_width + d-1;  t = m_world[i-1][d-1];   Portal* p = isPortal(t); if(p != nullptr){t=p->getDestination(); in = t->getRow()*m_width+t->getCol();} if(t->clearPath()){ nL->push_back(graph_nodes.at(in)); dL->push_back(1.1); dD->push_back('7');}}
            if(d < m_width-1){                      in = i * m_width + d+1;      t = m_world[i][d+1];     Portal* p = isPortal(t); if(p != nullptr){t=p->getDestination(); in = t->getRow()*m_width+t->getCol();} if(t->clearPath()){ nL->push_back(graph_nodes.at(in)); dL->push_back(1); dD->push_back('6');}}
            if(d > 0){                              in = i * m_width + d-1;      t = m_world[i][d-1];     Portal* p = isPortal(t); if(p != nullptr){t=p->getDestination(); in = t->getRow()*m_width+t->getCol();} if(t->clearPath()){ nL->push_back(graph_nodes.at(in)); dL->push_back(1); dD->push_back('4');}}
            if(i < m_height-1){                     in = (i+1) * m_width + d;    t = m_world[i+1][d];     Portal* p = isPortal(t); if(p != nullptr){t=p->getDestination(); in = t->getRow()*m_width+t->getCol();} if(t->clearPath()){ nL->push_back(graph_nodes.at(in)); dL->push_back(1); dD->push_back('2');}}
            if(i > 0){                              in = (i-1) * m_width + d;    t = m_world[i-1][d];     Portal* p = isPortal(t); if(p != nullptr){t=p->getDestination(); in = t->getRow()*m_width+t->getCol();} if(t->clearPath()){ nL->push_back(graph_nodes.at(in)); dL->push_back(1); dD->push_back('8');}}



            //add list to Nodes
            graph_nodes.at(i * m_width + d)->adjazenz_list = nL;
            graph_nodes.at(i * m_width + d)->adjazenz_distance = dL;
            graph_nodes.at(i * m_width + d)->adjazenz_direction = dD;
        }
    }
}


Portal* Level::isPortal(Tile* t){
    Portal* p = dynamic_cast<Portal*>(t);
    if(p != nullptr)
        return p;
    return nullptr;
}



vector<Character*> Level::getHumanCharacters(){
    vector<Character*> humans;
    for(Character* c : m_characters){
        if(c->getHuman()){
              humans.push_back(c);
        }
    }
    return humans;
}

































