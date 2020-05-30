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
            mvaddch(i,j,lvl->getTile(i,j)->getIcon());
        }
    }

}

UserInterface::~UserInterface(){
    endwin();
}



int UserInterface::move() {
    mvaddstr(0,25, "1-9 to Move, press 0 to close");
    int key = getch();
    //return the key, check in main game loop if the game should continue
    //Debug
    //logging::Logger::instance()->log(logging::INFO, "return " + std::to_string(key));
    return key;
}
