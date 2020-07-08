#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H
#include "controller.h"
#include "string"

class GuardController : public Controller
{
public:
    GuardController(std::string pattern);

    virtual int move() override;

private:
    std::string pattern;
    size_t step;
};

#endif // GUARDCONTROLLER_H
