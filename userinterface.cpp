#include "userinterface.h"
#include <ncurses.h>

UserInterface::UserInterface()
{

}

void UserInterface::draw(Level *lvl) {
    //draw line by line, start top left
    for(int i = 0; i < lvl->getHeight(); i++) {
        for(int j = 0; j < lvl->getWidth(); j++) {
            mvaddch(i,j,lvl->getTile(i,j)->getIcon());
        }
    }

}
