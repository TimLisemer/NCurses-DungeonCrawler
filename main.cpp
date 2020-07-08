#include <iostream>
#include "dungeoncrawler.h"
#include "logger.h"

logging::Logger *logging::Logger::m_inst = nullptr;
bool DungeonCrawler::m_running = true;

int main()
{
    DungeonCrawler game = DungeonCrawler();
    game.play();

    return EXIT_SUCCESS;
}
