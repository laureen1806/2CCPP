#ifndef CELL_H
#define CELL_H

#include "bonus.h"

class Cell {
private:
    bool occupied;
    int playerId;
    BonusType bonus;

public:
    Cell();
    bool isEmpty() const;
    void setOccupied(int playerId);
    void setBonus(BonusType bonus);
    BonusType getBonus() const;
};

#endif
