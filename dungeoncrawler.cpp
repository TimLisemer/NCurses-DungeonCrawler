#include "dungeoncrawler.h"
#include "logger.h"
#include <ncurses.h>

//Init UI, Level, Character
DungeonCrawler::DungeonCrawler() {
    m_ui = new UserInterface();
    Level* level = new Level(m_ui);
    m_levels.push_back(level);
}

//Delete DC
DungeonCrawler::~DungeonCrawler() {
    delete m_ui;
    for (Level* l : m_levels) {
        delete l;
    }
}

void DungeonCrawler::play() {
    logging::Logger::instance()->set(logging::INFO, "/tmp/DungeonCrawler.log");
    logging::Logger::instance()->log(logging::INFO, "DungeonCrawler start");

    bool running = true;
    while(running) {
        logging::Logger::instance()->log(logging::INFO, "running");

        for(Level* level : m_levels){

            m_ui->draw(level);
            for(Character* c : level->getCharacters()) {
                int key = c->move();
                if(key == 48) {
                    running = false;
                    break;
                }
                m_ui->move(c->getTile()->getRow(), c->getTile()->getCol(), c, level);
            }

        }
    }
    logging::Logger::instance()->log(logging::INFO, "Game has been Exited");
}

