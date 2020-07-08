#include "potion.h"

Potion::Potion(const std::string &name, int amount, int hp) : Consumable(name, amount), hp(hp)
{

}

Potion::Potion(const Potion &p) : Consumable(p.getName(),p.getAmount()), hp(p.hp)
{

}

Potion::~Potion()
{

}

int Potion::getHp() const
{
    return hp;
}

void Potion::onDrop(Character *c, Tile *)
{
    //check if potion stack not empty and player cant overheal
    if(m_amount > 0)  {
        m_amount--;
        if(c->getCurrentHP() + hp > c->getMaxHP()) c->addCurrHp(c->getMaxHP() - c->getCurrentHP());
        else c->addCurrHp(hp);
    }
}
