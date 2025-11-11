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
    Terrain terrain = Terrain::Empty;
    int playerId = -1;
    BonusType bonus = BonusType::NONE; // adapte selon ta définition
    char symbol = '.'; // utilisé seulement si tu affiches via symbol

public:
    Cell() = default;

    bool isEmpty() const { return terrain == Terrain::Empty && playerId == -1; }
    bool isGrass() const { return terrain == Terrain::Grass; }
    void setGrass(int pid) { terrain = Terrain::Grass; playerId = pid; symbol = char('0' + (pid % 10)); }
    void setStone() { terrain = Terrain::Stone; symbol = '#'; }
    void setBonus(BonusType type) { terrain = Terrain::Bonus; bonus = type; symbol = '*'; }

    int getPlayerId() const { return playerId; }
    Terrain getTerrain() const { return terrain; }
    BonusType getBonus() const { return bonus; }

    char getSymbol() const { return symbol; }
    void setSymbol(char s) { symbol = s; }
};

#endif
