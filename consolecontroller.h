#ifndef CONSOLECONTROLLER_H
#define CONSOLECONTROLLER_H
#include "controller.h"

class ConsoleController : public Controller
{
public:
    ConsoleController();

    virtual int move() override;
};

#endif // CONSOLECONTROLLER_H
