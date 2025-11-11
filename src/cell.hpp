#ifndef CELL_HPP
#define CELL_HPP

#include "bonusSquare.hpp"

enum class Terrain {
    Empty,
    Grass,
    Stone,
    Bonus
};

class Cell {
private:
    Terrain terrain;
    int playerId;
    BonusType bonus;
    char symbol;

public:
    Cell();

    bool isEmpty() const;
    bool isGrass() const;
    void setGrass(int pid);
    void setStone();
    void setBonus(BonusType type);

    int getPlayerId() const;
    Terrain getTerrain() const;
    BonusType getBonus() const;

    char getSymbol() const;
    void setSymbol(char s);
};


#endif
