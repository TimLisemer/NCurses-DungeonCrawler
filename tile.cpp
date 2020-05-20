#include "tile.h"
#include "character.h"
#include "logger.h"


Tile::Tile(char icon, int row, int col) : m_icon(icon), m_row(row), m_col(col), m_character(nullptr){}

char Tile::getIcon() const{
    if(hasCharacter()){
        return getCharacter()->getIcon();
    }else{
        return m_icon;
    }
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

Floor* Floor::onEnter(Tile *fromTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Entered tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return this;
}

Floor* Floor::onLeave(Tile *destTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Left tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return this;
}



///
/// \brief Wall::Wall
///
Wall::Wall(const int row, const int col) : Tile('#', row, col){}

Wall* Wall::onEnter(Tile *fromTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Entered tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return nullptr;
}

Wall* Wall::onLeave(Tile *destTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Left tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return this;
}



///
/// \brief Portal::Portal
///
Portal::Portal(const int row, const int col) : Tile('O', row, col){}
//Portal::Portal(const int row, const int col, Portal* portalDestination) : Tile('O', row, col), m_destination(portalDestination){};

Portal* Portal::onEnter(Tile *fromTile){
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "Entered tile: " + std::to_string(getRow()) + " - " + std::to_string(getCol()));
    return m_destination;
}

Portal* Portal::onLeave(Tile *destTile){
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
































