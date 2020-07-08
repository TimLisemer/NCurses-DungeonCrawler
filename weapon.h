#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"

class Weapon : public Item
{
public:
    Weapon(const std::string &name, int strBonus);

    Weapon(const Weapon& w);

    virtual ~Weapon();

    virtual void onEquip(Character * c) override;

    virtual void onDrop(Character* c, Tile* tile) override;

    int getBonus() const;

private:
    int bonus;
};

#endif // WEAPON_H
