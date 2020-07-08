#include "guardcontroller.h"

GuardController::GuardController(std::string pattern) : pattern(pattern)
{
    step = 0;
}

int GuardController::move()
{
    //need to make a copy to return, because we need to increment but if we return the incremented value we mess up the pattern
    //and we cant increment after returning, so we return a copy
    int state = step;
    if(step == pattern.length()-1) step = 0;
    else step++;
    return pattern.at(state);
}
