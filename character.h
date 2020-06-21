#ifndef CHARACTER_H
#define CHARACTER_H
#include <vector>
using std::vector;
#include "userinterface.h"
#include "item.h"
#include "level.h"


using std::string;

class Tile;
class Controller;
class Item;
class Level;

class Character{

public:

    Character(Controller* controller, Level* level, const char icon, const int strenght, const int stamina);
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
    void setMaxHpMultiplier(const double multiplier);

    int getMaxHPBuffer() const;
    void setMaxHpBuffer(const int buffer);

    void addToInventory(Item* item);
    int getInventorySize() const;
    vector<Item*> m_items;

    Level* getLevel() const;

private:

    Tile* m_position;
    Controller* m_controller;
    Level* m_level;

    int m_maxHPBuffer;
    double m_maxHpMultiplier = 1.0;
    char m_icon;
    int m_strenght;
    int m_stamina;
    int m_hitPoints;
};

#endif // CHARACTER_H
