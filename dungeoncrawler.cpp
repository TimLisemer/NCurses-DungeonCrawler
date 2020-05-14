#include "dungeoncrawler.h"
#include "logger.h"
#include <ncurses.h>

//Init UI, Level, Character
DungeonCrawler::DungeonCrawler() {
    UI = new UserInterface();
    current = new Level();
    characters = std::vector<Character*>();
}

//Delete DC
DungeonCrawler::~DungeonCrawler() {
    delete UI;
    delete current;
    for (Character* c : characters) {
        delete c;
    }
}

void DungeonCrawler::play() {
    logging::Logger::instance()->set(logging::INFO, "/tmp/DungeonCrawler.log");
    logging::Logger::instance()->log(logging::INFO, "DungeonCrawler start");


    //create character
    characters.push_back(new Character('C'));
    //place character on level
    current->placeCharacter(characters.at(0), m_startRow, m_starCol);
    //set character tile to zero
    characters.at(0)->setTile(current->getTile(m_startRow,m_starCol));

    bool running = true;
    while(running) {
        logging::Logger::instance()->log(logging::INFO, "running");
        UI->draw(current);
        for(Character* c : characters) {
            int key = c->move();
            if(key == 48) {
                running = false;
                break;
            }
            move(c->getTile()->getRow(), c->getTile()->getCol(),key, c, current);
        }
    }

    logging::Logger::instance()->log(logging::INFO, "Game has been Exited");

}

void DungeonCrawler::move(int row, int col,int key, Character* c, Level* level) {
    //logging::Logger::instance()->log(logging::INFO, "inside move");

    switch(key){
        case '1':
            if(row+1 < current->getHeight() && col -1 >= 0)
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol() - 1));
            logging::Logger::instance()->log(logging::INFO, "Input 1");
            break;
        case '2':
            if(row+1 < current->getHeight()) {
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol()));
            logging::Logger::instance()->log(logging::INFO, "Input 2");
            break;
        case '3':
            if(row+1 < current->getHeight() && col+1 < current->getWidth())
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol() + 1));
            logging::Logger::instance()->log(logging::INFO, "Input 3");
            break;
        case '4':
            if(col-1 >= 0)
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow(), c->getTile()->getCol() - 1));
            logging::Logger::instance()->log(logging::INFO, "Input 4");
            break;
        case '6':
            if(col+1 < current->getWidth())
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow(), c->getTile()->getCol() + 1));
            logging::Logger::instance()->log(logging::INFO, "Input 6");
            break;
        case '7':
            if(row-1 >= 0 && col-1 >= 0)
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() -1, c->getTile()->getCol() - 1));
            logging::Logger::instance()->log(logging::INFO, "Input 7");
            break;
        case '8':
            if(row-1 >= 0)
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() - 1, c->getTile()->getCol()));
            logging::Logger::instance()->log(logging::INFO, "Input 8");
            break;
        case '9':
            if(row-1 >= 0 && col + 1 < current->getWidth())
            c->getTile()->moveTo(level->getTile(c->getTile()->getRow() - 1, c->getTile()->getCol() + 1));
            logging::Logger::instance()->log(logging::INFO, "Input 9");
            break;
        case '5':
            logging::Logger::instance()->log(logging::INFO, "Input 5");
            break;
        default:
                logging::Logger::instance()->log(logging::WARN, "Falsch Eingabe");

        }
    }
}

