#include "../src/tile.hpp"
#include "../src/board.hpp"
#include <algorithm>

// Constructeur
Tile::Tile(const std::vector<std::vector<int>>& shape)
    : shape(shape), width(shape[0].size()), height(shape.size()) {}

// Rotation 90° (transpose + reverse)
void Tile::rotate() {
    std::vector<std::vector<int>> rotated(width, std::vector<int>(height));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            rotated[j][height - i - 1] = shape[i][j];
        }
    }
    shape = rotated;
    std::swap(width, height);
}

// Flip horizontal
void Tile::flip() {
    for (auto& row : shape) {
        std::reverse(row.begin(), row.end());
    }
}

// Vérifie si la tuile peut être placée (logique à compléter)
bool Tile::canPlace(const Board& board, int row, int col) const {
    // TODO: vérifier si toutes les cases de la tuile rentrent dans le plateau
    // et ne chevauchent pas d'autres territoires
    return true;
}

// Getters
int Tile::getWidth() const { return width; }
int Tile::getHeight() const { return height; }
const std::vector<std::vector<int>>& Tile::getShape() const { return shape; }
