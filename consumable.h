#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include "item.h"

class Consumable : public Item
{
public:
    Consumable(const std::string &name, int amount);

    Consumable(const Consumable& c);

    virtual ~Consumable();

    virtual void onDrop(Character* c, Tile* tile) override;

    int getAmount() const;

protected:
    int m_amount;

};

#endif // CONSUMABLE_H
