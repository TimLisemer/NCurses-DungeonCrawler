#include "tile.h"
#include "character.h"
#include "logger.h"


Tile::Tile(char icon, int row, int col) : m_icon(icon), m_row(row), m_col(col), m_character(nullptr){}
Tile::Tile(int row, int col) : m_row(row), m_col(col), m_character(nullptr){}

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


Tile::~Tile(){

}


///
/// \brief Floor::Floor
///
Floor::Floor(const int row, const int col) : Tile('.', row, col){}
Floor::Floor(const char icon, const int row, const int col) : Tile(icon, row, col){}

Tile* Floor::onEnter(Tile *fromTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Entered tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return this;
}

Tile* Floor::onLeave(Tile *destTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Left tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return this;
}



///
/// \brief Wall::Wall
///
Wall::Wall(const int row, const int col) : Tile('#', row, col){}
Wall::Wall(const char icon, int row, const int col) : Tile(icon, row, col){}

Tile* Wall::onEnter(Tile *fromTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Entered tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return nullptr;
}

Tile* Wall::onLeave(Tile *destTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Left tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return this;
}



///
/// \brief Portal::Portal
///
Portal::Portal(const int row, const int col) : Tile('O', row, col){}
Portal::Portal(const char icon, const int row, const int col) : Tile(icon, row, col){}
//Portal::Portal(const int row, const int col, Portal* portalDestination) : Tile('O', row, col), m_destination(portalDestination){};

Tile* Portal::onEnter(Tile *fromTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Entered tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return m_destination;
}

Tile* Portal::onLeave(Tile *destTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Left tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return this;
}


Portal* Portal::getDestination() const{
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


//Bin ich komplett behindert oder mach ich das hier übertrieben kompliziert???
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
Door::Door(const int row, const int col) : Tile(row, col), Floor(row, col), Wall(row, col) {
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
Switch::Switch(const int row, const int col) : Tile(row, col), Floor(row, col){
    changeState(false);
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





























