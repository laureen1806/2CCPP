#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "cell.hpp"
#include "tile.hpp"
#include "bonus.hpp"
#include "player.hpp"

class Board {
private:
    std::vector<std::vector<Cell>> grid;
    int size;

public:
    // Constructeur
    Board(int size);

    // Placement de tuile
    bool placeTile(Tile& tile, Player& player, int row, int col);

    // Gestion des bonus
    void addBonus(const BonusSquare& bonus);

    // Affichage
    void render() const;

    // Getters
    int getSize() const;
};

#endif
