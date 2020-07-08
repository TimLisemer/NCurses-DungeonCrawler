#ifndef POTION_H
#define POTION_H
#include "consumable.h"

class Potion: public Consumable
{
public:
    Potion(const std::string &name, int amount, int hp);

    Potion(const Potion& p);

    virtual ~Potion();

    int getHp() const;

    virtual void onDrop(Character*c, Tile* t) override;

private:
    int hp;
};

#endif // POTION_H
