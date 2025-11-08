#ifndef CELL_HPP
#define CELL_HPP

#include "bonus.hpp"

class Cell {
private:
    bool occupied;
    int playerId;       // -1 si vide
    BonusType bonus;    // type de bonus éventuel

public:
    // Constructeur
    Cell();

    // Méthodes
    bool isEmpty() const;
    void setOccupied(int playerId);
    void setBonus(BonusType bonus);

    // Getters
    int getPlayerId() const;
    BonusType getBonus() const;
};

#endif
