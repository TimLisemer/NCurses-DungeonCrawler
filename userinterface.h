#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "level.h"
#include "controller.h"
#include <ncurses.h>

class UserInterface : public Controller
{
public:
    UserInterface();

    virtual ~UserInterface();

    void draw(Level* lvl);

    void drawStatusBar(Character* c);

    void drawInventory(Character* c);

    virtual int move() override;

private:
    WINDOW* stats;
    WINDOW* inventory;
    WINDOW* ctrls;
    WINDOW* lvl;
};

#endif // USERINTERFACE_H
