#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"
#include "tile.h"
#include "bonus.h"
#include "player.h"

class Board {
private:
    std::vector<std::vector<Cell>> grid;
    int size;

public:
    Board(int size);
    bool placeTile(Tile& tile, Player& player, int row, int col);
    void addBonus(const BonusSquare& bonus);
    void render() const;

    int getSize() const;
};

#endif
