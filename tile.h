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
class Item;

class Tile{

private:

    Level* m_level;
    Character* m_character;
    Item* m_item;

    char m_icon;
    const int m_row;
    const int m_col;

    bool m_passable = false;

public:

    explicit

    Tile(char icon, int row, int col, Level* level, Item* item);
    Tile(int row, int col, Level* level, Item* item);

    virtual ~Tile();

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

    Item* getItem() const;
    void setItem(Item* item);
    bool hasItem() const;
    void pickupItem(Tile* toTile);

    virtual bool clearPath();
    virtual void setPassable(const bool passable);
    virtual bool isPassable() const;
};


///
/// \brief The Floor class
///
class Floor : public virtual Tile{

public:

    Floor(const int row, const int col, Level* level);
    Floor(const char icon, const int row, const int col, Level* level);

    Floor(const int row, const int col, Level* level, Item* item);
    Floor(const char icon, const int row, const int col, Level* level, Item* item);
};



///
/// \brief The Wall class
///
class Wall : public virtual Tile{

public:
    Wall(const int row, const int col, Level* level);
    Wall(const char icon, const int row, const int col, Level* level);

    Wall(const int row, const int col, Level* level, Item* item);
    Wall(const char icon, const int row, const int col, Level* level, Item* item);

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

    Portal(const int row, const int col, Level* level, Item* item);
    Portal(const int row, const int col, const int destRow, const int destCol, Level* level, Item* item);

    Portal(const char icon, const int row, const int col, Level* level, Item* item);
    Portal(const char icon, const int row, const int col, const int destRow, const int destCol, Level* level, Item* item);

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

    Door(const int row, const int col, Level* level, Item* item);

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


    Switch(const int row, const int col, Level* level, Item* item);
    Switch(const int row, const int col, const vector<int> m_destRows, const vector<int> m_destCols, Level* level, Item* item);

    void changeState(bool state);

    virtual Tile* onEnter(Tile* fromTile);
    virtual void attach(Passive* passive);
    virtual void detach(Passive* passive);

};




///
/// \brief The Lever class
///
class Lever : public Floor, Active{

private:

    vector<int> m_destRows;
    vector<int> m_destCols;

public:

    Lever(const int row, const int col, Level* level);
    Lever(const int row, const int col, const vector<int> m_destRows, const vector<int> m_destCols, Level* level);


    Lever(const int row, const int col, Level* level, Item* item);
    Lever(const int row, const int col, const vector<int> m_destRows, const vector<int> m_destCols, Level* level, Item* item);

    virtual Tile* onEnter(Tile* fromTile);
    virtual void attach(Passive* passive);
    virtual void detach(Passive* passive);

};




///
/// \brief The Trap class
///
class Trap : public Floor{

public:

    Trap(const int row, const int col, Level* level, const int hitPoints);

    Trap(const int row, const int col, Level* level, Item* item, const int hitPoints);

    virtual Tile* onEnter(Tile* fromTile);

private:

    const int m_hitPoints;
    char m_hiddenIcon;
    bool m_defused = false;


};














































#endif // TILE_H
