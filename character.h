#ifndef CHARACTER_H
#define CHARACTER_H
class Tile;

class Character{

public:
    Character(char m_icon);
    char getIcon() const;
    Tile* getTile();
    void setTile(Tile* tile);
    int move();

private:
    const char m_icon;
    Tile* m_position;
};

#endif // CHARACTER_H
