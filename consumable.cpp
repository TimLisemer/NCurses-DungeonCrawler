#include "consumable.h"

Consumable::Consumable(const std::string &name, int amount) : Item(name), m_amount(amount)
{

}

Consumable::Consumable(const Consumable &c) : Item(c.getName()), m_amount(c.m_amount)
{

}

Consumable::~Consumable()
{

}

void Consumable::onDrop(Character *, Tile *)
{
    m_amount--;
}

int Consumable::getAmount() const
{
    return m_amount;
}
