#include "item.h"


///
/// \brief Item::Item
///
Item::Item(const std::string &name) : m_name(name){}

void Item::onEquip(Character *c){

    //To Do

}

void Item::onDrop(Character *c, Tile *tile){

    //To Do

}


std::string Item::getName() const{
    return m_name;
}




///
/// \brief Consumable::Consumable
///
Consumable::Consumable(const std::string &name, int amount) : Item(name), m_amount(amount) {}

bool Consumable::consume(Character *c){

    //To Do
    return false;
}


///
/// \brief Weapon::Weapon
///
Weapon::Weapon(const std::string &name, int strBonus) : Item(name), m_strBonus(strBonus) {}

int Weapon::getStrBonus() const{
    return m_strBonus;
}

void Weapon::onEquip(Character *c){

}

void Weapon::onDrop(Character *c, Tile *tile){

}



///
/// \brief Armor::Armor
///
Armor::Armor(const std::string &name, int staBonus) : Item(name), m_staBonus(staBonus) {}

int Armor::getStaBonus() const{
    return m_staBonus;
}

void Armor::onEquip(Character *c){

}

void Armor::onDrop(Character *c, Tile *tile){

}


///
/// \brief Potion::Potion
///
Potion::Potion(const std::string &name, int amount, int hp) : Consumable(name, amount), m_hp(hp) {}

int Potion::getHP() const{
    return m_hp;
}


void Potion::setHP(const int hp){
    m_hp = hp;
}



///
/// \brief Elixir::Elixir
///
Elixir::Elixir(const std::string &name, int amount, int hpMax) : Consumable(name, amount), m_hpMax(hpMax) {}


int Elixir::getHpMax() const{
    return m_hpMax;
}

void Elixir::setHpMax(const int hpMax){
    m_hpMax = hpMax;
}























