#include "../src/cell.hpp"

Cell::Cell() : terrain(Terrain::Empty), playerId(-1), bonus(BonusType::EXCHANGE) {}

bool Cell::isEmpty() const {
    return terrain == Terrain::Empty;
}

bool Cell::isGrass() const {
    return terrain == Terrain::Grass;
}

bool Cell::isStone() const {
    return terrain == Terrain::Stone;
}

void Cell::setGrass(int playerId) {
    terrain = Terrain::Grass;
    this->playerId = playerId;
}

void Cell::setStone() {
    terrain = Terrain::Stone;
    playerId = -1;
}

void Cell::setBonus(BonusType type) {
    terrain = Terrain::Bonus;
    bonus = type;
}

int Cell::getPlayerId() const {
    return playerId;
}

Terrain Cell::getTerrain() const {
    return terrain;
}

BonusType Cell::getBonus() const {
    return bonus;
}