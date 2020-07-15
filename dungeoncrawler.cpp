#include "dungeoncrawler.h"

//Init UI, Level, Character
DungeonCrawler::DungeonCrawler() {
    m_ui = new UserInterface();
    Level* level = new Level(m_ui);
    m_levels.push_back(level);
}

//Delete DC
DungeonCrawler::~DungeonCrawler() {
    for (Level* l : m_levels) {
        delete l;
    }
}

void DungeonCrawler::play() {
    logging::Logger::instance()->set(logging::INFO, "DungeonCrawler.log");
    logging::Logger::instance()->log(logging::INFO, "DungeonCrawler start");
    while(m_running) {
        logging::Logger::instance()->log(logging::INFO, "running");

        for(Level* level : m_levels){

            m_ui->draw(level);
            for(Character* c : level->getCharacters()) {
                bool keepRunning = false;
                for(Character* c : level->getHumanCharacters()){
                    if(c->alive()){
                        keepRunning = true;
                    }
                }
                if(!keepRunning){
                    m_running = false;
                }

                if(c->alive()){
                    c->move();
                    level->updateGraph();
                }
            }
        }
    }
    logging::Logger::instance()->log(logging::INFO, "Game has been Exited");
}


void DungeonCrawler::quit(){
    m_running = false;
}
