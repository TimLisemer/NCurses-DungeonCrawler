#ifndef TILE_H
#define TILE_H
#include <string>
#include "character.h"

using std::string;

class Tile
{
public:

    Tile();

    explicit

    Tile(char icon, int row, int col);

    char getIcon() const;

    const string& getType() const;

    int getRow() const;

    int getCol() const;

    const Tile* getDestination() const;

    bool hasCharacter() const;

    void setCharacter(Character* m_character);
    Character* getCharacter() const;

    bool moveTo(Tile* destTile);

    virtual Tile* onEnter(Tile* fromTile);

    virtual Tile* onLeave(Tile* toTile);

private:
    const int m_row;
    const int m_col;
    const char m_icon;
    Character* m_character;
};




///
/// \brief The Floor class
///
class Floor : public Tile{

public:

    Floor(const int row, const int col);

    virtual Floor* onEnter(Tile* fromTile);
    virtual Floor* onLeave(Tile* destTile);

};



///
/// \brief The Wall class
///
class Wall : public Tile{

public:
    Wall(const int row, const int col);

    virtual Wall* onEnter(Tile* fromTile);
    virtual Wall* onLeave(Tile* destTile);
};



///
/// \brief The Portal class
///
class Portal : public Tile{

private:

    //if type == Portal --> destination == destination Portal
    Portal* m_destination;

public:

    Portal(const int row, const int col);
    //Portal(const int row, const int col, Portal* portalDestination = nullptr);

    virtual Portal* onEnter(Tile* fromTile);
    virtual Portal* onLeave(Tile* destTile);

    Portal* getDestination() const;
    void setDestination(Portal* destination);
};





























#endif // TILE_H
