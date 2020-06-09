#ifndef CHARACTER_H
#define CHARACTER_H

#include "userinterface.h"
using std::string;

class Tile;
class Controller;

class Character{

public:
    Character(const char icon, Controller* controller);
    Character(const Character &character) = delete;
    ~Character();

    char getIcon() const;
    void setIcon(const char icon);
    Tile* getTile() const;
    void setTile(Tile* tile);
    Controller* getController() const;
    void setController(Controller* controller);
    int move();

private:
    char m_icon;
    Tile* m_position;
    Controller* m_controller;
};

#endif // CHARACTER_H
