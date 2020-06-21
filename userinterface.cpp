#include "userinterface.h"

Controller::Controller(){}

Controller::~Controller(){
    delete this;
}

int Controller::move(Character* c){
    return 0;
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
        m_HeaderWindow = newwin(11, 22, 1, 24);
        m_gameMenu = false;
        mvaddstr(2,25, "Press 1-9 to Move");
        mvaddstr(3,25, "Press 0 to Close");
        mvaddstr(4,25, "Press 5 to Pause");
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
        m_HeaderWindow = newwin(6, 22, 1, 24);
        mvaddstr(2,25, "Inventory");
    }
}


int UserInterface::move(Character* c) {

    int row = c->getTile()->getRow(), col = c->getTile()->getRow();
    Level* level = c->getLevel();

    if(m_firstStartup){
        setGameMenu(0, c);
        m_firstStartup = false;
    }

    int key = getch();

    //Check if Inventory is open to go back to Menu
    if(m_Inventory){
        logging::Logger::instance()->log(logging::INFO, "Input <any> (Close Inventory)");
        setGameMenu(1, c);
    }else{
        //Check Close Game Keys
        if(key == 27 || key == 'q' || key == '0'){
            //Quit Game
            logging::Logger::instance()->log(logging::INFO, "Input 0 (Quit Game)");
            DungeonCrawler::quit();
        }
        //Game Menu Keys
        if(m_gameMenu){
            if(key == 'i'){
                //Show Inventory
                logging::Logger::instance()->log(logging::INFO, "Input i (Show Inventory)");
                setGameMenu(2, c);
            }else{
                //show Game Header
                setGameMenu(0, c);
            }
        }else{
            //Game Keys
            switch(key){
                case '1':
                    if(row+1 < level->getHeight() && col -1 >= 0)
                    setGameMenu(0, c);
                    logging::Logger::instance()->log(logging::INFO, "Input 1 (DownLeft)");
                    break;
                case '2':
                    if(row+1 < level->getHeight()) {
                    setGameMenu(0, c);
                    logging::Logger::instance()->log(logging::INFO, "Input 2 (Down)");
                    break;
                case '3':
                    if(row+1 < level->getHeight() && col+1 < level->getWidth())
                    setGameMenu(0, c);
                    logging::Logger::instance()->log(logging::INFO, "Input 3 (DownRight)");
                    break;
                case '4':
                    if(col-1 >= 0)
                    setGameMenu(0, c);
                    logging::Logger::instance()->log(logging::INFO, "Input 4 (Left)");
                    break;
                case '6':
                    if(col+1 < level->getWidth())
                    setGameMenu(0, c);
                    logging::Logger::instance()->log(logging::INFO, "Input 6 (Right)");
                    break;
                case '7':
                    if(row-1 >= 0 && col-1 >= 0)
                    setGameMenu(0, c);
                    logging::Logger::instance()->log(logging::INFO, "Input 7 (UpperLeft)");
                    break;
                case '8':
                    if(row-1 >= 0)
                    setGameMenu(0, c);
                    logging::Logger::instance()->log(logging::INFO, "Input 8 (Up)");
                    break;
                case '9':
                    if(row-1 >= 0 && col + 1 < level->getWidth())
                    setGameMenu(0, c);
                    logging::Logger::instance()->log(logging::INFO, "Input 9 (UpperRight)");
                    break;
                case '5':
                    if(m_gameMenu){
                        setGameMenu(0, c);
                    }else{
                        setGameMenu(1, c);
                    }
                    logging::Logger::instance()->log(logging::INFO, "Input 5 (Open / Close GameMenu)");
                    break;
                default:
                        logging::Logger::instance()->log(logging::WARN, "Falsche Eingabe");

                }
            }
        }
    }
    return key;
}






StationaryController::StationaryController(){}

int StationaryController::move(Character*){
    return 5;
}


GuardController::GuardController(const int pattern){
    string textPattern = std::to_string(pattern);
    for(size_t i = 0; i < textPattern.size(); i++){
        m_pattern.push_back(textPattern.at(i));
    }
}


int GuardController::move(Character*){
    vector<int> newPattern;
    newPattern.push_back(m_pattern.at(m_pattern.size() - 1));
    for(size_t i = 0; i < m_pattern.size() -1; i++){
        newPattern.push_back(m_pattern.at(i));
    }
    m_pattern = newPattern;
    return m_pattern.at(1);
}


























