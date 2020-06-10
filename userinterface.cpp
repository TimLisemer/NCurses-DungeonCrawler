#include "userinterface.h"
#include <ncurses.h>

Controller::Controller(){}

Controller::~Controller(){
    delete this;
}

int Controller::move(){
    return 0;
}

UserInterface::UserInterface() {
    initscr();   // Init the screen
    noecho();    // Do not display text input
    cbreak();    // Do not wait for enter on input
    curs_set(0); // Let the cursor disappear
}

void UserInterface::draw(Level *lvl) {
    //draw line by line, start top left
    for(int i = 0; i < lvl->getHeight(); i++) {
        for(int j = 0; j < lvl->getWidth(); j++) {
            mvaddch(i + 11,j + 25,lvl->getTile(i,j)->getIcon());
        }
    }

}

UserInterface::~UserInterface(){
    endwin();
}



int UserInterface::move(int row, int col, Character* c, Level* level) {

    mvaddstr(2,25, "1-9 to Move, press 0 to close");
    string icon(1, c->getIcon());
    mvaddstr(4,25, std::string("Active Player    : " + icon).c_str());
    mvaddstr(5,25, std::string("Stats: Strenght  : " + std::to_string(c->getStrenght())).c_str());
    mvaddstr(6,25, std::string("       Stamina   : " + std::to_string(c->getStamina())).c_str());
    mvaddstr(7,25, std::string("       Hitpoints : " + std::to_string(c->getHitPoints())).c_str());
    mvaddstr(8,25, std::string("       Backpack  : " + std::to_string(0)).c_str());                     //////////// Einfügen

    int key = getch();

    switch(key){
        case '1':
            if(row+1 < level->getHeight() && col -1 >= 0)
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol() - 1));
            logging::Logger::instance()->log(logging::INFO, "Input 1");
            break;
        case '2':
            if(row+1 < level->getHeight()) {
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol()));
            logging::Logger::instance()->log(logging::INFO, "Input 2");
            break;
        case '3':
            if(row+1 < level->getHeight() && col+1 < level->getWidth())
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol() + 1));
            logging::Logger::instance()->log(logging::INFO, "Input 3");
            break;
        case '4':
            if(col-1 >= 0)
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow(), c->getTile()->getCol() - 1));
            logging::Logger::instance()->log(logging::INFO, "Input 4");
            break;
        case '6':
            if(col+1 < level->getWidth())
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow(), c->getTile()->getCol() + 1));
            logging::Logger::instance()->log(logging::INFO, "Input 6");
            break;
        case '7':
            if(row-1 >= 0 && col-1 >= 0)
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() -1, c->getTile()->getCol() - 1));
            logging::Logger::instance()->log(logging::INFO, "Input 7");
            break;
        case '8':
            if(row-1 >= 0)
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() - 1, c->getTile()->getCol()));
            logging::Logger::instance()->log(logging::INFO, "Input 8");
            break;
        case '9':
            if(row-1 >= 0 && col + 1 < level->getWidth())
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() - 1, c->getTile()->getCol() + 1));
            logging::Logger::instance()->log(logging::INFO, "Input 9");
            break;
        case '5':
            logging::Logger::instance()->log(logging::INFO, "Input 5");
            break;
        default:
                logging::Logger::instance()->log(logging::WARN, "Falsche Eingabe");

        }
    }
    return key;
}
