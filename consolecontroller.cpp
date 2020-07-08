#include "consolecontroller.h"
#include <ncurses.h>

ConsoleController::ConsoleController()
{

}

int ConsoleController::move()
{
    int key = getch();
    //return the key, check in main game loop if the game should continue
    return key;
}
