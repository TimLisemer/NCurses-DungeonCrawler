#include <iostream>
#include "dungeoncrawler.h"
#include "logger.h"
//14.05.2020
logging::Logger *logging::Logger::m_inst = nullptr;

int main()
{

    DungeonCrawler Game = DungeonCrawler();
    Game.play();

    return EXIT_SUCCESS;
}
