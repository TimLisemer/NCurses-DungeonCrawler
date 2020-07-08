#include "active.h"

Active::Active()
{

}


void Active::attach(Passive *add) {
    passives.push_back(add);
}

void Active::detach(Passive *rm) {
    for(unsigned int i = 0; i < passives.size(); i++) {
        if(passives.at(i) == rm) {
            //swap with last element and pop back to remove
            std::swap(passives.at(i), passives.at(passives.size()-1));
            passives.pop_back();
        }
    }
}
