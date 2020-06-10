#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "level.h"
#include "logger.h"
using std::string;

class Level;
class Character;

class Controller{

public:

    explicit
    Controller();
    virtual ~Controller();
    virtual int move();

};


class UserInterface : public Controller{


public:
    UserInterface();
    ~UserInterface();
    void draw(Level* lvl);

    virtual int move(int row, int col, Character* c, Level* level);
};

#endif // USERINTERFACE_H
