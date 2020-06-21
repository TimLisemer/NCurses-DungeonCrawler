#include "userinterface.h"

Controller::Controller(){}

Controller::~Controller(){
    delete this;
}

int Controller::move(Character *c){
    return getch();
}


bool Controller::setTile(Character *c, const int key){
    switch(key){
        case '1':
            if(c->getTile()->getRow()+1 < c->getLevel()->getHeight() && c->getTile()->getCol() -1 >= 0)
            return(c->getTile()->moveTo(c->getLevel()->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol() - 1)));
            break;
        case '2':
            if(c->getTile()->getRow()+1 < c->getLevel()->getHeight()) {
            return(c->getTile()->moveTo(c->getLevel()->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol())));
            break;
        case '3':
            if(c->getTile()->getRow()+1 < c->getLevel()->getHeight() && c->getTile()->getCol()+1 < c->getLevel()->getWidth())
            return(c->getTile()->moveTo(c->getLevel()->getTile(c->getTile()->getRow() + 1, c->getTile()->getCol() + 1)));
            break;
        case '4':
            if(c->getTile()->getCol()-1 >= 0)
            return(c->getTile()->moveTo(c->getLevel()->getTile(c->getTile()->getRow(), c->getTile()->getCol() - 1)));
            break;
        case '6':
            if(c->getTile()->getCol()+1 < c->getLevel()->getWidth())
            return(c->getTile()->moveTo(c->getLevel()->getTile(c->getTile()->getRow(), c->getTile()->getCol() + 1)));
            break;
        case '7':
            if(c->getTile()->getRow()-1 >= 0 && c->getTile()->getCol()-1 >= 0)
            return(c->getTile()->moveTo(c->getLevel()->getTile(c->getTile()->getRow() -1, c->getTile()->getCol() - 1)));
            break;
        case '8':
            if(c->getTile()->getRow()-1 >= 0)
            return(c->getTile()->moveTo(c->getLevel()->getTile(c->getTile()->getRow() - 1, c->getTile()->getCol())));
            break;
        case '9':
            if(c->getTile()->getRow()-1 >= 0 && c->getTile()->getCol() + 1 < c->getLevel()->getWidth())
            return(c->getTile()->moveTo(c->getLevel()->getTile(c->getTile()->getRow() - 1, c->getTile()->getCol() + 1)));
            break;
        case '5':
            return true;
            break;
        default:
            logging::Logger::instance()->log(logging::WARN, "Falsche Eingabe");
            return false;
        }
    }
    logging::Logger::instance()->log(logging::WARN, "Falsche Eingabe");
    return false;
}


UserInterface::UserInterface() {
    initscr();   // Init the screen
    noecho();    // Do not display text input
    cbreak();    // Do not wait for enter on input
    curs_set(0); // Let the cursor disappear
}

void UserInterface::draw(Level *lvl) {
    //draw line by line, start top left
    for(int i = 0; i < lvl->getHeight(); i++) {
        for(int j = 0; j < lvl->getWidth(); j++) {
            mvaddch(i + 13,j + 25,lvl->getTile(i,j)->getIcon());
        }
    }
}

UserInterface::~UserInterface(){
    endwin();
}

void UserInterface::setGameMenu(const int menu, Character* c){

    if(m_HeaderWindow != nullptr){
        wrefresh(m_HeaderWindow);
        delwin(m_HeaderWindow);
    }

    if(menu == 0){
        //Game Header
        m_HeaderWindow = newwin(11, 26, 1, 24);
        m_gameMenu = false;
        mvaddstr(2,25, "Press 1-9 to Move");
        mvaddstr(3,25, "Press 0 to Close");
        mvaddstr(4,25, "Press 5 to open Game Menu");
        string icon(1, c->getIcon());
        mvaddstr(6,25, std::string("Active Player    : " + icon).c_str());
        mvaddstr(7,25, std::string("Stats: Strenght  : " + std::to_string(c->getStrenght())).c_str());
        mvaddstr(8,25, std::string("       Stamina   : " + std::to_string(c->getStamina())).c_str());
        mvaddstr(9,25, std::string("       Hitpoints : " + std::to_string(c->getHitPoints())).c_str());
        mvaddstr(10,25, std::string("       Backpack  : " + std::to_string(c->getInventorySize())).c_str());
    }else if(menu == 1){
        //Game Menu
        m_HeaderWindow = newwin(6, 22, 1, 24);
        m_gameMenu = true;
        m_Inventory = false;
        mvaddstr(2,25, "Gamemenu");
        mvaddstr(4,25, "q: Quit Game");
        mvaddstr(5,25, "i: Open Inventory");
    }else if(menu == 2){
        //Inventory
        m_gameMenu = false;
        m_Inventory = true;
        m_HeaderWindow = newwin(12, 100, 1, 24);
        mvaddstr(2,25, "Inventory - Press i to close");
        if(c->getInventorySize() > 0){
            if(c->getInventorySize() > 1){
                mvaddstr(3,25, std::string("1 - " + std::to_string(c->getInventorySize()) + " to Consume / Drop Items").c_str());
            }else{
                mvaddstr(3,25, "1 to Consume / Drop Item");
            }

            for(int i = 1; i < c->getInventorySize() + 1; i++){
                Consumable* con = dynamic_cast<Consumable*>(c->m_items.at(i-1));
                if(con != nullptr){
                    mvaddstr(4+i,25, std::string(std::to_string(i) + ": " + c->m_items.at(i-1)->getName() + " (" + std::to_string(con->getAmount()) + ")").c_str());
                }else{
                    mvaddstr(4+i,25, std::string(std::to_string(i) + ": " + c->m_items.at(i-1)->getName()).c_str());
                }
            }
        }else{
            mvaddstr(4,25, "No Items in Inventory");
        }
    }
}


int UserInterface::move(Character* c) {

    if(m_firstStartup){
        setGameMenu(0, c);
        m_firstStartup = false;
    }

    bool pause = false;
    bool successfull = false;
    int key;

    do{
        key = getch();

        //Check Close Game Keys
        if(key == 27 || key == 'q' || key == '0'){
            //Quit Game
            logging::Logger::instance()->log(logging::INFO, "Input 0 (Quit Game)");
            DungeonCrawler::quit();
            break;
        }

        if(!pause){
            if(key != '5'){
                successfull = Controller::setTile(c, key);
                setGameMenu(0, c);
            }else{
                logging::Logger::instance()->log(logging::INFO, "Input 5 (Open Game Menu)");
                pause = true;
                setGameMenu(1, c);
            }
        }else{
            if(m_Inventory){
                if((key - 48) >= 1 && (key - 48) <= c->getInventorySize()){
                    logging::Logger::instance()->log(logging::INFO, "Input i (Consume / Drop Item)");

                    try {
                        Consumable* con = dynamic_cast<Consumable*>(c->m_items.at(key - 48 - 1));
                        if(con == nullptr){
                            Item* item = c->m_items.at(key - 48 - 1);
                            item->onDrop(c, c->getTile());
                            logging::Logger::instance()->log(logging::INFO, std::string("Dropped Item" + item->getName()));
                            setGameMenu(0, c);
                            pause = false;
                        }else{
                            if(con->consume(c)){
                                setGameMenu(0, c);
                                logging::Logger::instance()->log(logging::INFO, std::string("Consumed Item" + con->getName()));
                                pause = false;
                            }else{
                                logging::Logger::instance()->log(logging::INFO, std::string("Failed to Consume" + c->m_items.at(key - 48 - 1)->getName()));
                            }
                        }
                    }  catch(std::invalid_argument){}

                }else{
                    logging::Logger::instance()->log(logging::INFO, "Input i (Close Inventory)");
                    setGameMenu(1, c);
                }
            }else{
                if(key == 'i'){
                    logging::Logger::instance()->log(logging::INFO, "Input i (Show Inventory)");
                    setGameMenu(2, c);
                }else{
                    logging::Logger::instance()->log(logging::INFO, "Input i (Close Game Menu)");
                    setGameMenu(0, c);
                    pause = false;
                }
            }
        }
    }while (pause || !successfull);

    return key;
}






StationaryController::StationaryController(){}

int StationaryController::move(Character* c){
    Controller::setTile(c, 5);
    return 5;
}


GuardController::GuardController(const int pattern){
    string textPattern = std::to_string(pattern);
    for(size_t i = 0; i < textPattern.size(); i++){
        m_pattern.push_back(textPattern.at(i));
    }
}


int GuardController::move(Character* c){
    vector<int> newPattern;
    newPattern.push_back(m_pattern.at(m_pattern.size() - 1));
    for(size_t i = 0; i < m_pattern.size() -1; i++){
        newPattern.push_back(m_pattern.at(i));
    }
    if(Controller::setTile(c, newPattern.at(1))){
        m_pattern = newPattern;
    }
    return newPattern.at(1);
}


























