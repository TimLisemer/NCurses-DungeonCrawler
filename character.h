#ifndef CHARACTER_H
#define CHARACTER_H

#include "userinterface.h"
using std::string;

class Tile;
class Controller;

class Character{

public:
    Character(const char icon, Controller* controller);
    char getIcon() const;
    Tile* getTile() const;
    void setTile(Tile* tile);
    int move();

    void setName(const string name);
    string getName() const;

private:
    const char m_icon;
    string m_name;
    Tile* m_position;
    Controller* m_controller;
};

#endif // CHARACTER_H
