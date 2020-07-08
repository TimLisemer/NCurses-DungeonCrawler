#include "dungeoncrawler.h"
#include "logger.h"
#include <ncurses.h>
#include "attackcontroller.h"

DungeonCrawler::DungeonCrawler() {
    UI = new UserInterface();
    current = new Level();
    current->loadLevel("/home/stud/Programmierne//5-studi.map");
    current->createNodes();
    characters = std::vector<Character*>();
}

DungeonCrawler::~DungeonCrawler() {
    delete UI;
    delete current;
    for (Character* c : characters) {
        delete c;
    }
}

void DungeonCrawler::play() {
    logging::Logger::instance()->set(logging::INFO, "DungeonCrawler.log");
    logging::Logger::instance()->log(logging::INFO, "DungeonCrawler start");

    //add characters on level (maybe after load) to vector
    for(int i = 0; i < current->getHoehe(); i++) {
        for(int j = 0; j < current->getBreite(); j++) {
            if(current->getTile(i,j)->hasCharacter()) {
                characters.push_back(current->getTile(i,j)->getCharacter());
            }
        }
    }

    //set target
    for(Character* c : characters) {
        if(dynamic_cast<AttackController*>(c->getController())) {
            for(Character* c2 : characters) {
                if(!c2->isNPC()) dynamic_cast<AttackController*>(c->getController())->setTarget(c2);
            }

        }
    }

    bool m_running = true;
    while(m_running) {
        for(int i = 0; static_cast<size_t>(i) < characters.size(); i++) {
            Character* c = characters.at(i);
            if(!c->isNPC() && !c->isAlive()) m_running = false;
            if(!c->isAlive()) continue;

            UI->draw(current);
            UI->drawStatusBar(c);

            int key = c->move();
            if(key == '0') {
                m_running = false;
                break;
            }
            if(key == '5') {
                UI->drawInventory(c);
                i--; // so characters turn is not skipped
            }
            switchPosition(c->getTile()->getRow(), c->getTile()->getCol(), key);
        }
    }
    logging::Logger::instance()->log(logging::INFO, "Game has been Exited");

    endwin();
}

void DungeonCrawler::switchPosition(int row, int col, int key) {
    //a lot of copy paste so i put it in a separate function
    //updates fields and checks for out of bounds
    //could combine key comparison with oob check to save a few lines, but this looks better
    if(key == '1') {
        if(row+1 < current->getHoehe() && col -1 >= 0) {
            current->getTile(row,col)->moveTo(current->getTile(row+1,col-1));
        }
    } else if(key == '2') {
        if(row+1 < current->getHoehe()) {
            current->getTile(row,col)->moveTo(current->getTile(row+1,col));
        }
    } else if(key == '3') {
        if(row+1 < current->getHoehe() && col+1 < current->getBreite()) {
            current->getTile(row,col)->moveTo(current->getTile(row+1,col+1));
        }
    } else if(key == '4') {
        if(col-1 >= 0) {
            current->getTile(row,col)->moveTo(current->getTile(row,col-1));
        }
    } else if(key == '6') {
        if(col+1 < current->getBreite()) {
            current->getTile(row,col)->moveTo(current->getTile(row,col+1));
        }
    } else if(key == '7') {
        if(row-1 >= 0 && col-1 >= 0) {
            current->getTile(row,col)->moveTo(current->getTile(row-1,col-1));
        }
    } else if(key == '8') {
        if(row-1 >= 0) {
            current->getTile(row,col)->moveTo(current->getTile(row-1,col));
        }
    } else if(key == '9') {
        if(row-1 >= 0 && col + 1 < current->getBreite()) {
            current->getTile(row,col)->moveTo(current->getTile(row-1,col+1));
        }
    }
}
