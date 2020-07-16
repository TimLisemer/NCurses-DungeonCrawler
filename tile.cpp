#include "tile.h"
#include "character.h"
#include "logger.h"


Tile::Tile(char icon, int row, int col, Level* level, Item* item) : m_level(level), m_character(nullptr), m_item(item), m_icon(icon), m_row(row), m_col(col) {}
Tile::Tile(int row, int col, Level* level, Item* item) : m_level(level), m_character(nullptr), m_item(item), m_row(row), m_col(col){}


Tile::~Tile(){
    delete m_item;
}


char Tile::getIcon() const{
    if(hasCharacter()){
        return getCharacter()->getIcon();
    }else{
        if(hasItem()){
            return '*';
        }else{
            return m_icon;
        }
    }
}

void Tile::setIcon(const char Icon){
    m_icon = Icon;
}


int Tile::getRow() const {
    return m_row;
}

int Tile::getCol() const {
    return m_col;
}

Level* Tile::getLevel() const{
    return m_level;
}


bool Tile::hasCharacter() const{
    if(getCharacter() != nullptr)
        return true;
    return false;
}

void Tile::setCharacter(Character *character) {
    this->m_character = character;
}


bool Tile::moveTo(Tile* destTile){
    if(hasCharacter()){
        Tile* abandonedTile = onLeave(destTile);
        if(abandonedTile != nullptr){
            Tile* enterTile = destTile->onEnter(abandonedTile);
            if(enterTile != nullptr){
                getCharacter()->setTile(enterTile);
                enterTile->setCharacter(abandonedTile->getCharacter());
                abandonedTile->setCharacter(nullptr);
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}


Tile* Tile::onEnter([[maybe_unused]]Tile *fromTile) {
    return this;
}

Tile* Tile::onLeave(Tile *toTile) {
    if(toTile->hasCharacter()){
        if((getCharacter()->getHuman() && !toTile->getCharacter()->getHuman()) || (!getCharacter()->getHuman() && toTile->getCharacter()->getHuman())){
            getCharacter()->Attack(toTile->getCharacter());
            if(toTile->getCharacter()->alive()){
                toTile->getCharacter()->Attack(getCharacter());
                if(!getCharacter()->alive()){
                    setCharacter(nullptr);
                }
                return nullptr;
            }else{
                toTile->setCharacter(nullptr);
                pickupItem(toTile);
                return this;
            }
        }else{
            return nullptr;
        }
    }else{
        pickupItem(toTile);
        return this;
    }
}


Character* Tile::getCharacter() const{
    return m_character;
}


Item* Tile::getItem() const{
    return m_item;
}

void Tile::setItem(Item *item){
    m_item = item;
}

bool Tile::hasItem() const{
    if(getItem() == nullptr){
        return false;
    }else{
        return true;
    }
}

void Tile::pickupItem(Tile* toTile){
    if(getCharacter()->getHuman()){
        if(toTile->hasItem()){
            getCharacter()->addToInventory(toTile->getItem());
            toTile->setItem(nullptr);
        }
    }
}


bool Tile::clearPath(){
    if(!m_passable) return false;
    if(hasCharacter()) if(!getCharacter()->getHuman()) return false;
    return true;
}


void Tile::setPassable(const bool passable){
    m_passable = passable;
}

bool Tile::isPassable() const{
    return m_passable;
}






///
/// \brief Floor::Floor
///
Floor::Floor(const int row, const int col, Level* level) : Tile('.', row, col, level, nullptr){Tile::setPassable(true);}
Floor::Floor(const char icon, const int row, const int col, Level* level) : Tile(icon, row, col, level, nullptr){Tile::setPassable(true);}



Floor::Floor(const int row, const int col, Level* level, Item* item) : Tile('.', row, col, level, item){Tile::setPassable(true);}
Floor::Floor(const char icon, const int row, const int col, Level* level, Item* item) : Tile(icon, row, col, level, item){Tile::setPassable(true);}







///
/// \brief Wall::Wall
///
Wall::Wall(const int row, const int col, Level* level) : Tile('#', row, col, level, nullptr){Tile::setPassable(false);}
Wall::Wall(const char icon, int row, const int col, Level* level) : Tile(icon, row, col, level, nullptr){Tile::setPassable(false);}


Wall::Wall(const int row, const int col, Level* level, Item* item) : Tile('#', row, col, level, item){Tile::setPassable(false);}
Wall::Wall(const char icon, int row, const int col, Level* level, Item* item) : Tile(icon, row, col, level, item){Tile::setPassable(false);}

Tile* Wall::onEnter([[maybe_unused]]Tile *fromTile){
    return nullptr;
}







///
/// \brief Portal::Portal
///
Portal::Portal(const int row, const int col, Level* level) : Tile('O', row, col, level, nullptr){Tile::setPassable(true);}
Portal::Portal(const int row, const int col, const int destRow, const int destCol, Level* level) : Tile('O', row, col, level, nullptr), m_destRow(destRow), m_destCol(destCol){Tile::setPassable(true);}

Portal::Portal(const char icon, const int row, const int col, Level* level) : Tile(icon, row, col, level, nullptr){Tile::setPassable(true);}
Portal::Portal(const char icon, const int row, const int col, const int destRow, const int destCol, Level* level) : Tile(icon, row, col, level, nullptr), m_destRow(destRow), m_destCol(destCol){Tile::setPassable(true);}


Portal::Portal(const int row, const int col, Level* level, Item* item) : Tile('O', row, col, level, item){Tile::setPassable(true);}
Portal::Portal(const int row, const int col, const int destRow, const int destCol, Level* level, Item* item) : Tile('O', row, col, level, item), m_destRow(destRow), m_destCol(destCol){Tile::setPassable(true);}

Portal::Portal(const char icon, const int row, const int col, Level* level, Item* item) : Tile(icon, row, col, level, item){Tile::setPassable(true);}
Portal::Portal(const char icon, const int row, const int col, const int destRow, const int destCol, Level* level, Item* item) : Tile(icon, row, col, level, item), m_destRow(destRow), m_destCol(destCol){Tile::setPassable(true);}


Tile* Portal::onEnter([[maybe_unused]]Tile *fromTile){
    if(getDestination()->hasCharacter()) return nullptr;
    return getDestination();
}

Tile* Portal::getDestination(){
    if(m_destination == nullptr){
        m_destination = (Portal*) getLevel()->getTile(m_destRow, m_destCol);
    }
    return m_destination;
}

void Portal::setDestination(Portal* destination){
    m_destination = destination;
}




///
/// \brief Passive::Passive
///
Passive::Passive(){}

void Passive::notify(){}



///
/// \brief Active::Active
///
Active::Active(){}

void Active::activate(){
    for(auto p : m_PassiveList){
        p->notify();
    }
}


void Active::attach(Passive* passive){
    m_PassiveList.push_back(passive);
}

void Active::detach(Passive* passive){
    vector<Passive*> tempPassiveList;
    for(auto p : m_PassiveList){
        if(p != passive){
            tempPassiveList.push_back(p);
        }
    }
    m_PassiveList = tempPassiveList;
}




///
/// \brief Door::Door
///
Door::Door(const int row, const int col, Level* level) : Tile(row, col, level, nullptr), Floor(row, col, level), Wall(row, col, level) {
    changeState(false);
}


Door::Door(const int row, const int col, Level* level, Item* item) : Tile(row, col, level, item), Floor(row, col, level, item), Wall(row, col, level, item) {
    changeState(false);
}



void Door::setIcon(const char Icon){
    Floor::setIcon(Icon);
    Wall::setIcon(Icon);
}

void Door::changeState(bool state){
    m_state = state;
    if(state){
        setIcon('/');
        Tile::setPassable(true);
    }else{
        setIcon('X');
        Tile::setPassable(false);
    }
}

Tile* Door::onEnter(Tile *fromTile){
    if(m_state){
        return Floor::onEnter(fromTile);
    }else{
        return Wall::onEnter(fromTile);
    }
}

Tile* Door::onLeave(Tile *destTile){
    if(m_state){
        return Floor::onLeave(destTile);
    }else{
        return Wall::onLeave(destTile);
    }
}


void Door::notify(){
    changeState(!m_state);
}










///
/// \brief Switch::Switch
///
Switch::Switch(const int row, const int col, Level* level) : Tile(row, col, level, nullptr), Floor(row, col, level){
    changeState(false);
    Tile::setPassable(false);
}

Switch::Switch(const int row, const int col, const vector<int> destRows, const vector<int> destCols, Level* level) : Tile(row, col, level, nullptr), Floor(row, col, level), m_destRows(destRows), m_destCols(destCols){
    changeState(false);
    Tile::setPassable(false);
    if(destRows.size() != destCols.size()){
        throw new std::invalid_argument("Different size for destRows and destCols for Switch");
    }else{
        for(size_t i = 0; i < destRows.size(); i++){
            Passive* d = dynamic_cast<Passive*>(getLevel()->getTile(destRows[i], destCols[i]));
            if(d == nullptr) throw std::invalid_argument("tile.cpp - Switch - invalid dynamic cast");
            attach(d);
        }
    }
}






Switch::Switch(const int row, const int col, Level* level, Item* item) : Tile(row, col, level, item), Floor(row, col, level){
    changeState(false);
    Tile::setPassable(false);
}

Switch::Switch(const int row, const int col, const vector<int> destRows, const vector<int> destCols, Level* level, Item* item) : Tile(row, col, level, item), Floor(row, col, level), m_destRows(destRows), m_destCols(destCols){
    changeState(false);
    Tile::setPassable(false);
    if(destRows.size() != destCols.size()){
        throw new std::invalid_argument("Different size for destRows and destCols for Switch");
    }else{
        for(size_t i = 0; i < destRows.size(); i++){
            Passive* d = dynamic_cast<Passive*>(getLevel()->getTile(destRows[i], destCols[i]));
            if(d == nullptr) throw std::invalid_argument("tile.cpp - Switch - invalid dynamic cast");
            attach(d);
        }
    }
}


void Switch::changeState(bool state){
    m_state = state;
    if(state){
        setIcon('!');
        Switch::activate();
    }else{
        setIcon('?');
    }
}


Tile* Switch::onEnter(Tile *fromTile){
    if(!m_state){
        changeState(true);
    }
    return Floor::onEnter(fromTile);
}

void Switch::attach(Passive *passive){
    Active::attach(passive);
}

void Switch::detach(Passive *passive){
    Active::detach(passive);
}





///
/// \brief Lever::Lever
///
Lever::Lever(const int row, const int col, Level* level) : Tile('L', row, col, level, nullptr), Floor('L', row, col, level){Tile::setPassable(false);}

Lever::Lever(const int row, const int col, const vector<int> destRows, const vector<int> destCols, Level* level) : Tile('L', row, col, level, nullptr), Floor('L', row, col, level), m_destRows(destRows), m_destCols(destCols){
    Tile::setPassable(false);
    if(destRows.size() != destCols.size()){
        throw new std::invalid_argument("Different size for destRows and destCols for Switch");
    }else{
        for(size_t i = 0; i < destRows.size(); i++){
            Passive* d = dynamic_cast<Passive*>(getLevel()->getTile(destRows[i], destCols[i]));
            if(d == nullptr) throw std::invalid_argument("tile.cpp - Switch - invalid dynamic cast");
            attach(d);
        }
    }
}






Lever::Lever(const int row, const int col, Level* level, Item* item) : Tile('L', row, col, level, item), Floor('L', row, col, level){Tile::setPassable(false);}
Lever::Lever(const int row, const int col, const vector<int> destRows, const vector<int> destCols, Level* level, Item* item) : Tile('L', row, col, level, item), Floor('L', row, col, level), m_destRows(destRows), m_destCols(destCols){
    Tile::setPassable(false);
    if(destRows.size() != destCols.size()){
        throw new std::invalid_argument("Different size for destRows and destCols for Switch");
    }else{
        for(size_t i = 0; i < destRows.size(); i++){
            Passive* d = dynamic_cast<Passive*>(getLevel()->getTile(destRows[i], destCols[i]));
            if(d == nullptr) throw std::invalid_argument("tile.cpp - Switch - invalid dynamic cast");
            attach(d);
        }
    }
}

Tile* Lever::onEnter(Tile *fromTile){
    Lever::activate();
    return Floor::onEnter(fromTile);
}

void Lever::attach(Passive *passive){
    Active::attach(passive);
}

void Lever::detach(Passive *passive){
    Active::detach(passive);
}






///
/// \brief Trap::Trap
///
Trap::Trap(const int row, const int col, Level* level, const int hitPoints) : Tile('.', row, col, level, nullptr), Floor('.', row, col, level), m_hitPoints(hitPoints) {Tile::setPassable(true);}

Trap::Trap(const int row, const int col, Level* level, Item* item, const int hitPoints) : Tile('.', row, col, level, item), Floor('.', row, col, level, item), m_hitPoints(hitPoints) {Tile::setPassable(true);}


Tile* Trap::onEnter(Tile *fromTile){
    if(!m_defused){
        fromTile->getCharacter()->setHitPoints(fromTile->getCharacter()->getHitPoints() - m_hitPoints);
        m_defused = true;
        setIcon('T');
    }
    return Floor::onEnter(fromTile);
}














































