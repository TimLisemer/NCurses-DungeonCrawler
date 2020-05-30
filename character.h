#ifndef CHARACTER_H
#define CHARACTER_H

#include "userinterface.h"

class Tile;
class Controller;

class Character{

public:
    Character(const char icon, Controller* controller);
    char getIcon() const;
    Tile* getTile();
    void setTile(Tile* tile);
    int move();

private:
    const char m_icon;
    Tile* m_position;
    Controller* m_controller;
};

#endif // CHARACTER_H
