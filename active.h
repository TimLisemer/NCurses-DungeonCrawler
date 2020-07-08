#ifndef ACTIVE_H
#define ACTIVE_H
#include "passive.h"
#include <vector>

//make this class abstract as well?
class Active
{
public:
    Active();

    void attach(Passive* add);

    void detach(Passive* rm);

    virtual void activate() = 0;

protected:
    std::vector<Passive*> passives;
};

#endif // ACTIVE_H
