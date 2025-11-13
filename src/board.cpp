#include "../includes/board.hpp"
#include "../includesplayer.hpp"
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
            // Vérifie si un bonus est entouré sur les 4 côtés
            for (int r = 1; r < size - 1; ++r) {
                for (int c = 1; c < size - 1; ++c) {
                    Cell& center = grid[r][c];
                    if (!center.hasBonus()) continue;
                
                    bool surrounded =
                        grid[r - 1][c].getPlayerId() == player.getId() &&
                        grid[r + 1][c].getPlayerId() == player.getId() &&
                        grid[r][c - 1].getPlayerId() == player.getId() &&
                        grid[r][c + 1].getPlayerId() == player.getId();
                
                    if (surrounded) {
                        BonusType bonus = center.getBonusType();
                        center.clearBonus(); // le bonus est consommé
                    
                        if (bonus == BonusType::EXCHANGE) {
                            player.addCoupon();
                            std::cout << player.getName() << " gagne un coupon d’échange !\n";
                        } else if (bonus == BonusType::STONE) {
                            std::cout << player.getName() << " a débloqué un bonus Pierre !\n";
                            player.addCoupon(); // récompense alternative si besoin
                        } else if (bonus == BonusType::ROBBERY) {
                            std::cout << player.getName() << " a débloqué un bonus Vol !\n";
                            // Le jeu doit gérer cela au niveau Game
                        }
                    }
                }
            }
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
