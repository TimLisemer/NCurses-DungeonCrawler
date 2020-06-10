#include "tile.h"
#include "character.h"
#include "logger.h"


Tile::Tile(char icon, int row, int col, Level* level) : m_level(level), m_icon(icon), m_row(row), m_col(col), m_character(nullptr){}
Tile::Tile(int row, int col, Level* level) : m_level(level), m_row(row), m_col(col), m_character(nullptr){}


Tile::~Tile(){

    delete m_level;
    delete m_character;

}


char Tile::getIcon() const{
    if(hasCharacter()){
        return getCharacter()->getIcon();
    }else{
        return m_icon;
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


Tile* Tile::onEnter(Tile *fromTile) {
    return this;
}

Tile* Tile::onLeave(Tile *toTile) {
    return this;
}


Character* Tile::getCharacter() const{
    return m_character;
}








///
/// \brief Floor::Floor
///
Floor::Floor(const int row, const int col, Level* level) : Tile('.', row, col, level){}
Floor::Floor(const char icon, const int row, const int col, Level* level) : Tile(icon, row, col, level){}







///
/// \brief Wall::Wall
///
Wall::Wall(const int row, const int col, Level* level) : Tile('#', row, col, level){}
Wall::Wall(const char icon, int row, const int col, Level* level) : Tile(icon, row, col, level){}
//TODO
Tile* Wall::onEnter(Tile *fromTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Entered tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return nullptr;
}







///
/// \brief Portal::Portal
///
Portal::Portal(const int row, const int col, Level* level) : Tile('O', row, col, level){}
Portal::Portal(const int row, const int col, const int destRow, const int destCol, Level* level) : Tile('O', row, col, level), m_destRow(destRow), m_destCol(destCol){}

Portal::Portal(const char icon, const int row, const int col, Level* level) : Tile(icon, row, col, level){}
Portal::Portal(const char icon, const int row, const int col, const int destRow, const int destCol, Level* level) : Tile(icon, row, col, level), m_destRow(destRow), m_destCol(destCol){}


Tile* Portal::onEnter(Tile *fromTile){
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

Passive::~Passive(){
    delete this;
}

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

Active::~Active(){
    delete this;
}











///
/// \brief Door::Door
///
Door::Door(const int row, const int col, Level* level) : Tile(row, col, level), Floor(row, col, level), Wall(row, col, level) {
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
    }else{
        setIcon('X');
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
Switch::Switch(const int row, const int col, Level* level) : Tile(row, col, level), Floor(row, col, level){
    changeState(false);
}

Switch::Switch(const int row, const int col, const vector<int> destRows, const vector<int> destCols, Level* level) : Tile(row, col, level), Floor(row, col, level), m_destRows(destRows), m_destCols(destCols){
    changeState(false);

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




























