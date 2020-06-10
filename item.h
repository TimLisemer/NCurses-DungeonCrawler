#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include "character.h"


//class Character;
//class Tile;


///
/// \brief The Item class
///
class Item {

public:

    Item(const std::string &name);

    virtual void onEquip(Character *c);
    virtual void onDrop(Character *c, Tile *tile);
    virtual std::string getName() const;

private:

    std::string m_name;

};



///
/// \brief The Consumable class
///
class Consumable : public Item {

public:

    Consumable(const std::string &name, int amount);

    virtual bool consume(Character *c);

private:

    int m_amount;

};




///
/// \brief The Weapon class
///
class Weapon : public Item {

public:

    Weapon(const std::string &name, int strBonus);
    int getStrBonus() const;

    virtual void onEquip(Character *c);
    virtual void onDrop(Character *c, Tile *tile);


private:

    int m_strBonus;

};



///
/// \brief The Armor class
///
class Armor : public Item {

public:

    Armor(const std::string &name, int staBonus);
    int getStaBonus() const;

    virtual void onEquip(Character *c);
    virtual void onDrop(Character *c, Tile *tile);

private:

    int m_staBonus;

};



///
/// \brief The Potion class
///
class Potion : public Consumable {

public:

    Potion(const std::string &name, int amount, int hp);
    int getHP() const;
    void setHP(const int hp);

private:

    int m_hp;

};


///
/// \brief The Elixir class
///
class Elixir : public Consumable {

    Elixir(const std::string &name, int amount, int hpMax);
    int getHpMax() const;
    void setHpMax(const int hpMax);

private:

    int m_hpMax;

};
















































#endif // ITEM_H
