#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include "userinterface.h"
#include <vector>
#include "level.h"

class Level;

class DungeonCrawler {
public:
    DungeonCrawler();
    ~DungeonCrawler();
    void play();

private:
    UserInterface* m_ui;
    vector<Level*> m_levels;
};

#endif // DUNGEONCRAWLER_H
