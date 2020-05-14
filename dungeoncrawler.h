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
    /**
     * @param row row of the tile
     * @param col col of the tile
     * @param dir direction movement
     * @param c Charakter
     *
     */
    void move(int row, int col,int key, Character* c, Level* level);

private:
    const int m_startRow = 1, m_starCol = 1;
    UserInterface* UI;
    Level* current;
    std::vector<Character*> characters;
};

#endif // DUNGEONCRAWLER_H
