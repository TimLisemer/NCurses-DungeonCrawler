#ifndef TILE_H
#define TILE_H
#include <string>
#include <vector>

#include "character.h"
#include "level.h"

using std::vector;
using std::string;

class Character;
class Level;

class Tile{

private:
    Level* m_level;
    Character* m_character;

    char m_icon;
    const int m_row;
    const int m_col;

public:

    explicit

    Tile(char icon, int row, int col, Level* level);
    Tile(int row, int col, Level* level);

    virtual ~Tile() = 0;



    char getIcon() const;
    void setIcon(const char Icon);

    const string& getType() const;

    int getRow() const;

    int getCol() const;

    bool hasCharacter() const;

    Level* getLevel() const;

    virtual void setCharacter(Character* m_character);
    Character* getCharacter() const;

    bool moveTo(Tile* destTile);

    virtual Tile* onEnter(Tile* fromTile);

    virtual Tile* onLeave(Tile* toTile);

};


///
/// \brief The Floor class
///
class Floor : public virtual Tile{

public:

    Floor(const int row, const int col, Level* level);
    Floor(const char icon, const int row, const int col, Level* level);
};



///
/// \brief The Wall class
///
class Wall : public virtual Tile{

public:
    Wall(const int row, const int col, Level* level);
    Wall(const char icon, const int row, const int col, Level* level);
    //TODO REMOVE
    virtual Tile* onEnter(Tile* fromTile);
};



///
/// \brief The Portal class
///
class Portal : public Tile{

private:

    //if type == Portal --> destination == destination Portal
    Portal* m_destination = nullptr;
    int m_destRow, m_destCol;

public:

    Portal(const int row, const int col, Level* level);
    Portal(const int row, const int col, const int destRow, const int destCol, Level* level);

    Portal(const char icon, const int row, const int col, Level* level);
    Portal(const char icon, const int row, const int col, const int destRow, const int destCol, Level* level);

    virtual Tile* onEnter(Tile* fromTile);

    Tile* getDestination();
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
    virtual ~Active() = 0;

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

public:

    Door(const int row, const int col, Level* level);

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
    vector<int> m_destRows;
    vector<int> m_destCols;

    //const char m_enabled = '!', m_disabled = '?';

public:

    Switch(const int row, const int col, Level* level);
    Switch(const int row, const int col, const vector<int> m_destRows, const vector<int> m_destCols, Level* level);

    void changeState(bool state);

    virtual Tile* onEnter(Tile* fromTile);
    virtual void attach(Passive* passive);
    virtual void detach(Passive* passive);

};






















































#endif // TILE_H
