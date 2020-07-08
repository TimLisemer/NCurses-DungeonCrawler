#include "elixir.h"

Elixir::Elixir(const std::string &name, int amount, int hpmax) : Consumable(name, amount), hpmax(hpmax)
{

}

Elixir::Elixir(const Elixir &e) : Consumable(e.getName(), e.getAmount()), hpmax(e.hpmax)
{

}

Elixir::~Elixir()
{

}

int Elixir::getHpmax() const
{
    return hpmax;
}

void Elixir::onDrop(Character *c, Tile *)
{
    if(m_amount > 0)  {
        m_amount--;
        c->addMaxHp(hpmax);
        c->addCurrHp(hpmax);
    }
}
