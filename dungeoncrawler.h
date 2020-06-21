#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include "userinterface.h"
#include <vector>
#include "level.h"

class Level;
class UserInterface;

class DungeonCrawler {
public:
    DungeonCrawler();
    ~DungeonCrawler();
    void play();
    static void quit();
private:
    UserInterface* m_ui;
    vector<Level*> m_levels;
    static bool m_running;
};

#endif // DUNGEONCRAWLER_H
