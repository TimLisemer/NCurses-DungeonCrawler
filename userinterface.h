#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "level.h"
#include "logger.h"
#include <ncurses.h>
#include "dungeoncrawler.h"

using std::string;

class Level;
class Character;

class Controller{

public:

    explicit
    Controller();
    virtual ~Controller();
    virtual int move(Character* c);

};


class UserInterface : public Controller{

public:
    UserInterface();
    ~UserInterface();

    void draw(Level* lvl);

    virtual int move(Character* c);

private:

    //True = Menu Open, False = Menu Closed
    bool m_gameMenu = false;
    bool m_Inventory = false;

    //Needed to show the GameHeader at First Time Startup
    bool m_firstStartup = true;

    WINDOW* m_HeaderWindow = nullptr;

    //If m_gameMenu == true --> Show Game Menu else show Game Info and Stats
    void setGameMenu(const int menu, Character* c);

};

#endif // USERINTERFACE_H
