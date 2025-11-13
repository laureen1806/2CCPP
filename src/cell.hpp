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
    BonusType bonus = BonusType::NONE;
    char symbol;

public:
    Cell();

    bool isEmpty() const;
    bool isGrass() const;
    void setGrass(int pid);
    void setStone();

    int getPlayerId() const;
    Terrain getTerrain() const;
    BonusType getBonus() const;

    char getSymbol() const;
    void setSymbol(char s);

    bool hasBonus() const { return bonus != BonusType::NONE; }
    BonusType getBonusType() const { return bonus; }
    void setBonus(BonusType t) { bonus = t; terrain = Terrain::Bonus; }
    void clearBonus() { bonus = BonusType::NONE; }
};


#endif
