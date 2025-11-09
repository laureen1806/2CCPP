#include "../src/board.hpp"
#include "../src/player.hpp"
#include <iostream>

// Constructeur
Board::Board(int size) : size(size) {
    grid.resize(size, std::vector<Cell>(size));
}

// Place une tuile sur le plateau
bool Board::placeTile(Tile& tile, Player& player, int row, int col) {
    const auto& shape = tile.getShape();
    // 1) bounds and overlap check
    for (int i = 0; i < tile.getHeight(); ++i) {
        for (int j = 0; j < tile.getWidth(); ++j) {
            if (shape[i][j] == 0) continue;
            int r = row + i, c = col + j;
            if (r < 0 || c < 0 || r >= size || c >= size) return false;
            if (!grid[r][c].isEmpty() || grid[r][c].getTerrain() == Terrain::Stone) return false;
        }
    }
    // 2) apply placement
    for (int i = 0; i < tile.getHeight(); ++i) {
        for (int j = 0; j < tile.getWidth(); ++j) {
            if (shape[i][j] == 0) continue;
            int r = row + i, c = col + j;
            grid[r][c].setGrass(player.getId());
            // handle bonus trigger if cell had bonus before placement rules require
        }
    }
    return true;
}

// Ajoute un bonus sur le plateau
void Board::addBonus(const BonusSquare& bonus) {
    int r = bonus.getRow();
    int c = bonus.getCol();
    if (r >= 0 && r < size && c >= 0 && c < size) {
        grid[r][c].setBonus(bonus.getType());
    }
}

// Affiche le plateau
void Board::render() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            const Cell& cell = grid[i][j];
            char ch = '.';
            if (cell.getTerrain() == Terrain::Stone) ch = '#';
            else if (cell.getTerrain() == Terrain::Bonus) ch = '*';
            else if (cell.isGrass()) ch = '0' + (cell.getPlayerId() % 10);
            std::cout << ch << " ";
        }
        std::cout << "\n";
    }
}

// Getter
int Board::getSize() const { return size; }

const Cell& Board::at(int row, int col) const {
    return grid[row][col];
}

Cell& Board::at(int row, int col) {
    return grid[row][col];
}
