#ifndef BONUS_H
#define BONUS_H

#include "player.h"
#include "game.h"

enum class BonusType { EXCHANGE, STONE, ROBBERY };

class BonusSquare {
private:
    BonusType type;
    int row, col;

public:
    BonusSquare(BonusType type, int row, int col);
    void apply(Player& player, Game& game);

    BonusType getType() const;
    int getRow() const;
    int getCol() const;
};

#endif
