#include "item.h"


///
/// \brief Item::Item
///
Item::Item(const std::string &name) : m_name(name){}

Item::~Item(){}

void Item::onEquip(Character *c){

}

void Item::onDrop(Character *c, Tile *tile){

    vector<Item*> newItems;
    for(auto* i : c->m_items){
        if(i != this){
            newItems.push_back(i);
        }
    }
    c->m_items = newItems;
    tile->setItem(this);

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

int Consumable::getAmount() const{
    return m_amount;
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

    vector<Item*> newItems;
    for(auto* i : c->m_items){
        if(i != this){
            newItems.push_back(i);
        }
    }
    c->m_items = newItems;
    tile->setItem(this);

}



///
/// \brief Armor::Armor
///
Armor::Armor(const std::string &name, int staBonus) : Item(name), m_staBonus(staBonus) {}

int Armor::getStaBonus() const{
    return m_staBonus;
}

void Armor::onEquip(Character *c){
    c->setMaxHpMultiplier((20 + (c->getStamina() + m_staBonus) * 5) / (20 + (c->getStamina() * 5)));
}

void Armor::onDrop(Character *c, Tile *tile){
    if(!tile->hasItem()){
        c->setMaxHpMultiplier((20 + (c->getStamina()) * 5) / (20 + (c->getStamina() * 5)));

        vector<Item*> newItems;
        for(auto* i : c->m_items){
            if(i != this){
                newItems.push_back(i);
            }
        }
        c->m_items = newItems;
        tile->setItem(this);
    }
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























