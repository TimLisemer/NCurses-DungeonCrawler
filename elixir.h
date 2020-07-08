#ifndef ELIXIR_H
#define ELIXIR_H
#include "consumable.h"

class Elixir : public Consumable
{
public:
    Elixir(const std::string &name, int amount, int hpmax);

    Elixir(const Elixir& e);

    virtual ~Elixir();

    int getHpmax() const;

    virtual void onDrop(Character*c, Tile* t) override;

private:
    int hpmax;
};

#endif // ELIXIR_H
