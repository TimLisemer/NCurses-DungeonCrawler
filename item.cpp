#include "item.h"

Item::Item(const std::string &name) : m_name(name)
{

}

Item::Item(const Item &i)
{
    m_name = i.m_name;
}

Item::~Item()
{

}

void Item::onEquip(Character *)
{

}

void Item::onDrop(Character *, Tile *)
{

}

std::string Item::getName() const
{
    return m_name;
}
