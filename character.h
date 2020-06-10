#ifndef CHARACTER_H
#define CHARACTER_H

#include "userinterface.h"
using std::string;

class Tile;
class Controller;

class Character{

public:

    Character(Controller* controller, const char icon, const int strenght, const int stamina);
    Character(const Character &character) = delete;
    ~Character();

    Tile* getTile() const;
    void setTile(Tile* tile);
    Controller* getController() const;
    void setController(Controller* controller);

    int move();

    char getIcon() const;
    void setIcon(const char icon);

    int getStrenght() const;
    void setStrenght(const int strenght);

    int getStamina() const;
    void setStamina(const int stamina);

    int getHitPoints() const;
    void setHitPoints(const int hitPoints);

    int getMaxHP() const;

private:

    Tile* m_position;
    Controller* m_controller;

    char m_icon;
    int m_strenght;
    int m_stamina;
    int m_hitPoints;
};

#endif // CHARACTER_H
