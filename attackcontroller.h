#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H
#include <controller.h>
#include "level.h"

class AttackController : public Controller
{
public:
    AttackController(Level* level, Character* thisChar, Character* target = nullptr);

    virtual ~AttackController();

    virtual int move() override;

    void setTarget(Character* c);

    int move(Tile* position);

private:
    Level* level;
    Character* me;
    Character* target;
};

#endif // ATTACKCONTROLLER_H
