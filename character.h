#ifndef CHARACTER_H
#define CHARACTER_H
#include <vector>
using std::vector;
#include "userinterface.h"
#include "item.h"
#include "level.h"
#include "list.h"


using std::string;

class Tile;
class Controller;
class Item;
class Level;

class Character{

public:

    Character(Controller* controller, Level* level, const char icon, const int strenght, const int stamina, const bool human);
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
    List m_items;
    Level* getLevel() const;

    bool getHuman() const;
    bool alive() const;
    void Attack(Character* e);
    void Defense(Character* e);

private:

    Tile* m_position;
    Controller* m_controller;
    Level* m_level;

    bool m_Human;

    int m_maxHPBuffer = 0;
    double m_maxHpMultiplier = 1.0;
    char m_icon;
    int m_strenght = 0;
    int m_stamina = 0;
    int m_hitPoints = 0;
};

#endif // CHARACTER_H
