#ifndef CHARACTER_H
#define CHARACTER_H
#include "controller.h"
#include "list.h"
#include "item.h"

class Tile;
class Item;
class List;

class Character
{
public:
    Character(char icon, int strength, int stamina, bool isNPC = true);

    ~Character();

    char getIcon() const;

    Tile* getTile();

    void setTile(Tile* tile);

    void setController(Controller* ctrl);

    int getMaxHP() const;

    int getCurrentHP() const;

    int move();

    bool isNPC() const;

    bool isAlive() const;

    void takeDamage(int dmg);

    int getStrength() const;

    int getStamina() const;

    void pickupItem(Item* item);

    List* getItems() const;

    Controller *getController() const;

    void addMaxHp(int val);

    void addCurrHp(int val);

    void addStrength(int val);

    void addStamina(int val);

    void setAlive(bool value);

private:
    const char icon;
    Tile* position;
    Controller* controller;

    int baseHP = 20;
    int hp;
    int strength;
    int stamina;

    bool NPC;
    bool alive = true;

    List* items;
};

#endif // CHARACTER_H
