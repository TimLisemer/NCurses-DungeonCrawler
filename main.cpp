#include <iostream>
#include "dungeoncrawler.h"
#include "logger.h"

logging::Logger *logging::Logger::m_inst = nullptr;
bool DungeonCrawler::m_running = true;

int main(){

    DungeonCrawler Game = DungeonCrawler();
    Game.play();

    return EXIT_SUCCESS;
}
