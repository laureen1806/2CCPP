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


bool Tile::canPlace(const Board& board, int row, int col, int playerId) const {
    int n = board.getSize();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (shape[i][j] == 0) continue; // case vide de la tuile

            int r = row + i;
            int c = col + j;

            // Sort du plateau
            if (r < 0 || c < 0 || r >= n || c >= n)
                return false;

            const Cell& cell = board.at(r, c);

            // Déjà occupé par un autre joueur ou pierre
            if (!cell.isEmpty() || cell.isStone())
                return false;

            // Interdiction de toucher un autre territoire (voisin d'un autre joueur)
            for (auto [dr, dc] : std::vector<std::pair<int,int>>{{1,0},{-1,0},{0,1},{0,-1}}) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nc >= 0 && nr < n && nc < n) {
                    const Cell& neighbor = board.at(nr, nc);
                    if (neighbor.isGrass() && neighbor.getPlayerId() != playerId)
                        return false;
                }
            }
        }
    }

    return true;
}

// Getters
int Tile::getWidth() const { return width; }
int Tile::getHeight() const { return height; }
const std::vector<std::vector<int>>& Tile::getShape() const { return shape; }
