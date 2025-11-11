#include "cell.hpp"

Cell::Cell() : terrain(Terrain::Empty), playerId(-1), bonus(BonusType::NONE), symbol('.') {}

bool Cell::isEmpty() const { return terrain == Terrain::Empty && playerId == -1; }
bool Cell::isGrass() const { return terrain == Terrain::Grass; }
void Cell::setGrass(int pid) { terrain = Terrain::Grass; playerId = pid; symbol = char('0' + (pid % 10)); }
void Cell::setStone() { terrain = Terrain::Stone; symbol = '#'; playerId = -1; }
void Cell::setBonus(BonusType type) { terrain = Terrain::Bonus; bonus = type; symbol = '*'; }

int Cell::getPlayerId() const { return playerId; }
Terrain Cell::getTerrain() const { return terrain; }
BonusType Cell::getBonus() const { return bonus; }

char Cell::getSymbol() const { return symbol; }
void Cell::setSymbol(char s) { symbol = s; }
