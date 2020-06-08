#include "level.h"

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}

Level::Level() {

/*TODO
 * Insert Charakter
 */
    //Map Insert
    ifstream file("../Do12x-Team5MASTER-master/3.map");
    if (!file.good()) {
    throw std::invalid_argument("File not found!");
    }
    vector<Node> nodes;
    while (true) {
    Node node;
    file >> node;
    nodes.push_back(node);
    if (file.eof())
    break;
    }

    //get height
    for (const auto &n : nodes) {
        if (n.name == "Map Information") {
            m_height = n.get<int>("rows");
            m_width = n.get<int>("cols");
        }else if (n.name == "Character") {
            m_startRow = n.get<int>("row");
            m_starCol = n.get<int>("col");
            m_CharacterName = n.get<string>("controller");
        }
    }


    //create rows
    m_world = new Tile**[m_height];

    //create cols
    for(int i = 0; i < m_height; i++) {
        m_world[i] = new Tile*[m_width];
    }

    //create elements
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
        }else if (n.name == "Portal") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            m_world[row][col] = new Portal(row, col, this);
        }else if (n.name == "Door") {
            int row = n.get<int>("row");
            int col = n.get<int>("col");
            m_world[row][col] = new Door(row, col, this);
        }
    }


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

void Level::placeCharacter(Character *c) {
    m_world[m_startRow][m_starCol]->setCharacter(c);
    c->setName(m_CharacterName);
    c->setTile(getTile(m_startRow, m_starCol));
}
