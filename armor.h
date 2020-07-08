#ifndef ARMOR_H
#define ARMOR_H
#include "item.h"

class Armor : public Item
{
public:
    Armor(const std::string &name, int staBonus);

    Armor(const Armor& a);

    virtual ~Armor();

    virtual void onEquip(Character* c) override;

    virtual void onDrop(Character* c, Tile* tile) override;

    int getBonus() const;

private:
    int bonus;
};

#endif // ARMOR_H
