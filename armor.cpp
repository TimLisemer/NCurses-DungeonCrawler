#include "armor.h"

Armor::Armor(const std::string &name, int staBonus) : Item(name), bonus(staBonus)
{

}

Armor::Armor(const Armor &a) : Item(a.getName()), bonus(a.bonus)
{

}

Armor::~Armor()
{

}

void Armor::onEquip(Character *c)
{
    c->addStamina(bonus);
    c->addCurrHp(bonus*5);
}

void Armor::onDrop(Character *c, Tile *tile)
{
    if(tile->getItem()) return;

    c->addStamina(-bonus);
    tile->setItem(this);
    c->addCurrHp(-5*bonus);
}

int Armor::getBonus() const
{
    return bonus;
}
