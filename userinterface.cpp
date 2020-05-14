#include "userinterface.h"
#include <ncurses.h>

UserInterface::UserInterface()
{
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
