#include "../src/bonusSquare.hpp"

BonusSquare::BonusSquare(BonusType type, int row, int col)
    : type(type), row(row), col(col) {}

BonusType BonusSquare::getType() const {
    return type;
}

int BonusSquare::getRow() const {
    return row;
}

int BonusSquare::getCol() const {
    return col;
}
