#ifndef TILE_H
#define TILE_H
#include <string>
#include <vector>

#include "character.h"

using std::vector;
using std::string;

class Tile{
public:

    Tile();

    explicit

    Tile(char icon, int row, int col);
    Tile(int row, int col);

    char getIcon() const;
    void setIcon(const char Icon);

    const string& getType() const;

    int getRow() const;

    int getCol() const;

    bool hasCharacter() const;

    virtual void setCharacter(Character* m_character);
    Character* getCharacter() const;

    bool moveTo(Tile* destTile);

    virtual Tile* onEnter(Tile* fromTile);

    virtual Tile* onLeave(Tile* toTile);

    virtual ~Tile() = 0;

private:
    char m_icon;
    const int m_row;
    const int m_col;
    Character* m_character;
};


///
/// \brief The Floor class
///
class Floor : public virtual Tile{

public:

    Floor(const int row, const int col);
    Floor(const char icon, const int row, const int col);

    virtual Tile* onEnter(Tile* fromTile);
    virtual Tile* onLeave(Tile* destTile);

};



///
/// \brief The Wall class
///
class Wall : public virtual Tile{

public:
    Wall(const int row, const int col);
    Wall(const char icon, const int row, const int col);

    virtual Tile* onEnter(Tile* fromTile);
    virtual Tile* onLeave(Tile* destTile);
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
    Portal(const char icon, const int row, const int col);
    //Portal(const int row, const int col, Portal* portalDestination = nullptr);

    virtual Tile* onEnter(Tile* fromTile);
    virtual Tile* onLeave(Tile* destTile);

    Portal* getDestination() const;
    void setDestination(Portal* destination);
};


///
/// \brief The Active class
///
class Passive{

public:

    explicit
    Passive();
    virtual ~Passive();

    virtual void notify();

};


///
/// \brief The Actice class
///
class Active{

private:

    vector<Passive*> m_PassiveList;

public:

    explicit
    Active();
    ~Active();

    virtual void attach(Passive* passive);
    virtual void detach(Passive* passive);
    void activate();



};


///
/// \brief The Door class
///
class Door : public Floor, Wall, public Passive{

private:

    //false = Door Closed | true = Door open
    bool m_state = false;

    //const char m_opened = '/', m_closed = 'X';

public:

    Door(const int row, const int col);

    void setIcon(const char Icon);
    void changeState(bool state);
    virtual void notify();

    virtual Tile* onEnter(Tile* fromTile);
    virtual Tile* onLeave(Tile* destTile);



};



///
/// \brief The Switch class
///
class Switch : public Floor, Active{

private:

    //false = Switch Disabled | true = Switch enabled
    bool m_state = false;

    //const char m_enabled = '!', m_disabled = '?';

public:

    Switch(const int row, const int col);

    void changeState(bool state);

    virtual Tile* onEnter(Tile* fromTile);
    virtual void attach(Passive* passive);
    virtual void detach(Passive* passive);

};






















































#endif // TILE_H
