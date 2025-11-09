#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "cell.hpp"
#include "tile.hpp"
#include "bonusSquare.hpp"
#include "player.hpp"

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

    const Cell& at(int row, int col) const;
    Cell& at(int row, int col);
};

#endif
