#include "level.h"

Level::Level() : m_height(20), m_width(20) {
    //create rows
    m_world = new Tile**[m_height];

    //create cols
    for(int i = 0; i < m_height; i++) {
        m_world[i] = new Tile*[m_width];
    }

    //create elements
    for(int i = 0; i < m_height; i++) {
        for(int d = 0; d < m_width; d++) {
            if(i == 0 || i == m_height - 1 || d == 0 || d == m_width - 1){
                m_world[i][d] = new Wall(i, d);
            }else{
                m_world[i][d] = new Floor(i, d);
            }
        }
    }

    delete m_world[3][3];
    Portal* p = new Portal(3, 3);
    m_world[3][3] = p;
    delete m_world[7][7];
    Portal* p2 = new Portal(7, 7);
    m_world[7][7] = p2;
    p->setDestination(p2);
    p2->setDestination(p);

    delete m_world[15][11];
    delete m_world[15][12];
    delete m_world[15][13];
    m_world[15][11] = new Wall(15, 11);
    Door* d1 = new Door(15, 12);
    m_world[15][12] = d1;
    m_world[15][13] = new Wall(15, 13);

    delete m_world[12][9];
    Switch* S1 = new Switch(12, 9);
    m_world[12][9] = S1;
    S1->attach(d1);
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

Level::Level(int hoehe, int breite) : m_height(hoehe), m_width(breite) {

}

Tile* Level::getTile(int row, int col) {
    return m_world[row][col];
}

int Level::getHeight() const {
    return m_height;
}

int Level::getWidth() const {
    return m_width;
}

const Tile* Level::getTile(int row, int col) const {
    return m_world[row][col];
}

void Level::placeCharacter(Character *c, int row, int col) {
    m_world[row][col]->setCharacter(c);
}
