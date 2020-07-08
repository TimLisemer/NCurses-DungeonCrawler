#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include "userinterface.h"
#include <vector>

class DungeonCrawler
{
public:
    DungeonCrawler();
    ~DungeonCrawler();

    void play();

    void switchPosition(int row, int col, int dir);
    static void quit();
private:
    UserInterface* UI;
    Level* current;
    std::vector<Character*> characters;
    static bool m_running;
};

#endif // DUNGEONCRAWLER_H
