#include "attackcontroller.h"

AttackController::AttackController(Level* level,Character* thisChar, Character* target) : level(level), me(thisChar), target(target)
{

}

AttackController::~AttackController()
{

}

void AttackController::setTarget(Character *c)
{
    target = c;
}

int AttackController::move()
{
    return *level->getPath(me->getTile(), target->getTile()).begin();
}

