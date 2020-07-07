#include "item.h"


///
/// \brief Item::Item
///
Item::Item(const std::string &name) : m_name(name){}

Item::~Item(){}

void Item::onEquip(Character *c){

}

void Item::onDrop(Character *c, Tile *tile){

    List newItems;
    for(auto* i : c->m_items){
        if(i != this){
            newItems.pushBack(i);
        }
    }
    c->m_items = newItems;
    tile->setItem(this);

}


std::string Item::getName() const{
    return m_name;
}




///
/// \brief Weapon::Weapon
///
Weapon::Weapon(const std::string &name, int strBonus) : Item(name), m_strBonus(strBonus) {}

int Weapon::getStrBonus() const{
    return m_strBonus;
}

void Weapon::onEquip(Character *c){
    c->setStrenght(c->getStrenght() + getStrBonus());
}

void Weapon::onDrop(Character *c, Tile *tile){

    if(!tile->hasItem()){
        c->setStrenght(c->getStrenght() - getStrBonus());

        List newItems;
        for(auto* i : c->m_items){
            if(i != this){
                newItems.pushBack(i);
            }
        }
        c->m_items = newItems;
        tile->setItem(this);
    }

}



///
/// \brief Armor::Armor
///
Armor::Armor(const std::string &name, int staBonus) : Item(name), m_staBonus(staBonus) {}

int Armor::getStaBonus() const{
    return m_staBonus;
}

void Armor::onEquip(Character *c){
    c->setMaxHpMultiplier(double(20 + ((c->getStamina() + m_staBonus) * 5)) / double(20 + (c->getStamina() * 5)));
}

void Armor::onDrop(Character *c, Tile *tile){
    if(!tile->hasItem()){
        c->setMaxHpMultiplier(1.0);

        List newItems;
        for(auto* i : c->m_items){
            if(i != this){
                newItems.pushBack(i);
            }
        }
        c->m_items = newItems;
        tile->setItem(this);
    }
}



///
/// \brief Consumable::Consumable
///
Consumable::Consumable(const std::string &name, int amount) : Item(name), m_amount(amount) {}

bool Consumable::consume(Character *c){

    return false;
}

int Consumable::getAmount() const{
    return m_amount;
}

void Consumable::setAmount(const int Amount){
    m_amount = Amount;
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


bool Potion::consume(Character *c){
    bool returner;
    if(c->getHitPoints() + getHP() >= c->getMaxHP() && c->getHitPoints() < c->getMaxHP()){
        c->setHitPoints(c->getMaxHP());
        setAmount(getAmount() - 1);
        returner = true;
    } else if(c->getHitPoints() + getHP() < c->getMaxHP()){
        c->setHitPoints(c->getHitPoints() + getHP());
        setAmount(getAmount() - 1);
        returner = true;
    }else returner = false;
    if(getAmount() <= 0){
        List newItems;
        for(auto* i : c->m_items){
            if(i != this){
                newItems.pushBack(i);
            }
        }
        c->m_items = newItems;
    }
    return returner;
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


bool Elixir::consume(Character *c){
    c->setMaxHpBuffer(c->getMaxHPBuffer() + getHpMax());
    setAmount(getAmount() - 1);
    if(getAmount() <= 0){
        List newItems;
        for(auto* i : c->m_items){
            if(i != this){
                newItems.pushBack(i);
            }
        }
        c->m_items = newItems;
    }
    return true;
}






















