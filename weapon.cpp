#include "weapon.h"

Weapon::Weapon(const std::string &name, int strBonus) : Item(name), bonus(strBonus)
{

}

Weapon::Weapon(const Weapon &w) : Item(w.getName()), bonus(w.bonus)
{

}

Weapon::~Weapon()
{

}

void Weapon::onEquip(Character *c)
{
    c->addStrength(bonus);
}

void Weapon::onDrop(Character *c, Tile *tile)
{
    if(tile->getItem()) return;

    c->addStrength(-bonus);
    tile->setItem(this);
}

int Weapon::getBonus() const
{
    return bonus;
}
