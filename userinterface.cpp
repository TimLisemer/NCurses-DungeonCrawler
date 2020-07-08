#include "userinterface.h"
#include <ncurses.h>
#include <string>
#include "list"
#include "consumable.h"
#include "armor.h"
#include "weapon.h"

#define BASE_OFFSET_X 1
#define BASE_OFFSET_Y 1
#define STATS_OFFSET_X 25
#define INV_OFFSET_X STATS_OFFSET_X
#define CTRLS_OFFSET_X STATS_OFFSET_X + STATS_WIDTH + 1

#define DEFAULT 0
#define STATS 1
#define INV 2
#define LEVEL 3

#define STATS_WIDTH  20
#define STATS_HEIGHT 7
#define INV_WIDTH 45
#define INV_HEIGHT 10
#define CTRLS_WIDTH INV_WIDTH - STATS_WIDTH
#define CTRLS_HEIGHT STATS_HEIGHT
#define LVL_WIDTH 22
#define LVL_HEIGHT 17

UserInterface::UserInterface()
{
    initscr(); // Init the screen
    noecho();    // Do not display text input
    cbreak();    // Do not wait for enter on input

    curs_set(0); //disable cursor

    //start color needs to be called to use color
    start_color();

    //init color pairs
    init_pair(DEFAULT, COLOR_BLACK, COLOR_WHITE);
    init_pair(STATS, COLOR_BLACK, COLOR_RED);
    init_pair(INV, COLOR_BLACK, COLOR_GREEN);
    init_pair(LEVEL, COLOR_BLACK, COLOR_BLUE);

    //initialize windows
    //create stats win & bg
    stats = newwin(STATS_HEIGHT,STATS_WIDTH,BASE_OFFSET_Y, BASE_OFFSET_X + STATS_OFFSET_X);
    wbkgd(stats, COLOR_PAIR(STATS));

    //create inv win & bg
    inventory = newwin(INV_HEIGHT,INV_WIDTH,BASE_OFFSET_Y + STATS_HEIGHT + 1, BASE_OFFSET_X + INV_OFFSET_X);
    wbkgd(inventory, COLOR_PAIR(INV));

    //create controls info window
    ctrls = newwin(CTRLS_HEIGHT, CTRLS_WIDTH, BASE_OFFSET_Y, CTRLS_OFFSET_X);
    wbkgd(ctrls,COLOR_PAIR(STATS));
    wclear(ctrls);
    box(ctrls,0,0);

    mvwaddstr(ctrls,1,1,"Board | Inventory");
    mvwaddstr(ctrls,2,1,"----------------------");
    mvwaddstr(ctrls,3,1,"7 8 9 | f -> use/drop");
    mvwaddstr(ctrls,4,1,"4 5 6 | w/s -> up/down");
    mvwaddstr(ctrls,5,1,"1 2 3 | 0 -> exit");

    //create lvl window
    lvl = newwin(LVL_HEIGHT, LVL_WIDTH, BASE_OFFSET_Y, BASE_OFFSET_X);
    wbkgd(lvl, COLOR_PAIR(LEVEL));
    wclear(lvl);
    box(lvl,0,0);
}

UserInterface::~UserInterface() {

}

void UserInterface::draw(Level *level) {
    //draw line by line, start top left
    for(int i = 0; i < level->getHoehe(); i++) {
        for(int j = 0; j < level->getBreite(); j++) {
            mvwaddch(lvl, i+1, BASE_OFFSET_Y + j,level->getTile(i,j)->getIcon());
        }
    }
    //refresh windows ctrls and lvl
    touchwin(ctrls);
    touchwin(lvl);
    wrefresh(ctrls);
    wrefresh(lvl);
}

void UserInterface::drawStatusBar(Character *c) {
    wclear(stats);
    //ncurses hat sich gewehrt den concat in mvwaddstr zu machen >:(, string auf länge des windows buffern
    string info = "Icon: ";
    info += c->getIcon();
    // if(STATS_WIDTH - info.length()) to prevent negative length exception
    mvwaddstr(stats,1,1, info.c_str());
    info = "HP: " + std::to_string(c->getCurrentHP()) + "/" + std::to_string(c->getMaxHP());
    mvwaddstr(stats,2,1, info.c_str());
    info = "Stamina: " + std::to_string(c->getStamina());
    mvwaddstr(stats,3,1,info.c_str());
    info = "Strength: " + std::to_string(c->getStrength());
    mvwaddstr(stats,4,1, info.c_str());
    info = "Position: " + std::to_string(c->getTile()->getRow()) + "-" + std::to_string(c->getTile()->getCol());
    mvwaddstr(stats,5,1, info.c_str());
    box(stats,0,0);
    wrefresh(stats);
}

void UserInterface::drawInventory(Character *c)
{
    wbkgd(inventory, COLOR_PAIR(INV));
    List* items = c->getItems();
    if(items->empty()) return;

    char d = 'a';
    List::iterator selected = items->begin();

    while(d != '0') {
        //clear screen
        wclear(inventory);
        box(inventory,0,0);
        wrefresh(inventory);


        if(d == 'w') {
            try {
                --selected;;
            }  catch (std::exception& e) { }
        } else if (d == 's') {
            List::iterator copy = selected;
            if(!(++copy == items->end())) ++selected;
        } else if (d == 'f') {
            if(dynamic_cast<Consumable*>(*selected)) {
                //use potion, if stack empty remove potion from items
                dynamic_cast<Consumable*>(*selected)->onDrop(c, c->getTile());
                if(dynamic_cast<Consumable*>(*selected)->getAmount() == 0) {
                    delete *selected; //delete data in now empty slot before it gets removed
                    items->remove(*selected);
                    //reset to beginning
                    selected = items->begin();
                }
            }
            else if(!c->getTile()->getItem()) {
                //remove deletes the element but not the data
                (*selected)->onDrop(c,c->getTile());
                items->remove(*selected);
                //reset to beginning
                selected = items->begin();
            }
        }
        //so we dont get an error handling nullptrs
        if(items->empty()) break;
        size_t count = 2;
        string info = "Inventory:  ";
        mvwaddstr(inventory,1,1, info.c_str());
        for(List::iterator it = items->begin(); it != items->end(); ++it) {
            info = "";
            if(it == selected) {
                info = "> ";
            }
            info += (*it)->getName();
            if(dynamic_cast<Consumable*>(*it)) info += " |" + std::to_string(dynamic_cast<Consumable*>(*it)->getAmount()) + "|";
            mvwaddstr(inventory,count,1, info.c_str());
            count++;
        }
        drawStatusBar(c);
        wrefresh(stats);
        wrefresh(inventory);
        d = getch();
    }
    //close inv
    wbkgd(inventory, COLOR_PAIR(DEFAULT));
    werase(inventory);
    wrefresh(inventory);
}

int UserInterface::move() {
    int key = getch();
    //return the key, check in main game loop if the game should continue
    return key;
}
