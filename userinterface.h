#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "level.h"

class Level;

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

    virtual int move();
};

#endif // USERINTERFACE_H
