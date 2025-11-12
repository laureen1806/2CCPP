#include "../src/tile.hpp"
#include "../src/board.hpp"
#include "../src/cell.hpp"
#include "../src/player.hpp"
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
bool Tile::canPlace(const Board& board, int row, int col, const Player& player) const {
    int n = board.getSize();
    auto shape = getShape();

    bool touchesTerritory = false;

    for (int r = 0; r < (int)shape.size(); ++r) {
        for (int c = 0; c < (int)shape[r].size(); ++c) {
            if (shape[r][c] == 0) continue;

            int rr = row + r;
            int cc = col + c;

            // Vérifier limites
            if (rr < 0 || rr >= n || cc < 0 || cc >= n) return false;

            const Cell& cell = board.at(rr, cc);

            // Interdiction de recouvrir une case déjà occupée
            if (!cell.isEmpty()) return false;

            // Interdiction de recouvrir la base du joueur
            auto [baseRow, baseCol] = player.getBase();
            if (rr == baseRow && cc == baseCol) return false;

            // Vérifier la connexion au territoire du joueur
            // On regarde les 4 voisins
            const int dr[4] = {-1, 1, 0, 0};
            const int dc[4] = {0, 0, -1, 1};
            for (int k = 0; k < 4; ++k) {
                int nr = rr + dr[k];
                int nc = cc + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    const Cell& neighbor = board.at(nr, nc);
                    if (neighbor.isGrass() && neighbor.getPlayerId() == player.getId()) {
                        touchesTerritory = true;
                    }
                }
            }
        }
    }

    // Il faut au moins une connexion
    return touchesTerritory;
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
