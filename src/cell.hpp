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
    int playerId;       // -1 si vide
    BonusType bonus;    // type de bonus éventuel

public:
    Cell();

    bool isEmpty() const;
    bool isGrass() const;
    void setGrass(int playerId);
    void setStone();
    void setBonus(BonusType type);

    int getPlayerId() const;
    Terrain getTerrain() const;
    BonusType getBonus() const;
};

#endif
