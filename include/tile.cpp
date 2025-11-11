#include "../src/tile.hpp"
#include "../src/board.hpp"
#include "../src/cell.hpp"
#include <algorithm>
#include <iostream>

// Constructeur sécurisé
Tile::Tile(const std::vector<std::vector<int>>& s)
    : shape(s),
      width(s.empty() ? 0 : s[0].size()),
      height(s.size()) {}

      // Rotation 90° (transpose + reverse)
void Tile::rotate() {
    if (shape.empty()) return;
    std::vector<std::vector<int>> rotated(width, std::vector<int>(height));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            rotated[j][height - i - 1] = shape[i][j];
        }
    }
    shape = rotated;
    std::swap(width, height);
}

// Flip horizontal (miroir gauche-droite)
void Tile::flipH() {
    for (auto& row : shape) {
        std::reverse(row.begin(), row.end());
    }
}

// Flip vertical (miroir haut-bas)
void Tile::flipV() {
    std::reverse(shape.begin(), shape.end());
}

// Vérifie si la tuile peut être placée
bool Tile::canPlace(const Board& board, int row, int col) const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (shape[i][j] == 0) continue;

            int r = row + i;
            int c = col + j;

            // Vérifie les limites
            if (r < 0 || c < 0 || r >= board.getSize() || c >= board.getSize()) {
                std::cerr << "Placement hors limites (" << r << "," << c << ")\n";
                return false;
            }

            // Vérifie si la case est libre
            const Cell& cell = board.at(r, c);
            if (!cell.isEmpty() || cell.getTerrain() == Terrain::Stone) {
                std::cerr << "Collision avec une case occupée (" << r << "," << c << ")\n";
                return false;
            }
        }
    }
    return true;
}

// Affichage console de la tuile
void Tile::print() const {
    for (const auto& row : shape) {
        for (int val : row) {
            std::cout << (val ? "■" : ".") << " ";
        }
        std::cout << "\n";
    }
}
