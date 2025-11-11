#include "../src/rendererCLI.hpp"
#include <iostream>

// Affiche le plateau
void RendererCLI::displayBoard(const Board& board) const {
    int n = board.getSize();
    std::cout << "   ";
    for (int c = 0; c < n; ++c) std::cout << char('A' + (c % 26)) << " ";
    std::cout << "\n";

    for (int r = 0; r < n; ++r) {
        std::cout << char('A' + (r % 26)) << "  ";
        for (int c = 0; c < n; ++c) {
            const Cell& cell = board.at(r, c);
            char ch = '.';
            if (cell.getTerrain() == Terrain::Stone) ch = '#';
            else if (cell.getTerrain() == Terrain::Bonus) ch = '*';
            else if (cell.isGrass()) ch = '0' + (cell.getPlayerId() % 10); // show player id digit
            std::cout << ch << " ";
        }
        std::cout << "\n";
    }
}

// Affiche l'état d'un joueur
void RendererCLI::displayPlayerStatus(const Player& player) const {
    std::cout << "Joueur: " << player.getName()
              << " | Couleur: " << player.getColor()
              << " | Coupons: " << player.getCoupons() << std::endl;
}

void RendererCLI::displayBoardWithPreview(const Board& board,
                                          const std::vector<Player>& players,
                                          const Tile& tile,
                                          int row, int col) const {
    // copie du plateau
    auto grid = board.getGrid();

    // dessiner la tuile en overlay
    const auto& shape = tile.getShape();
    for (int r = 0; r < (int)shape.size(); ++r) {
        for (int c = 0; c < (int)shape[r].size(); ++c) {
            if (shape[r][c] == 1) {
                int rr = row + r;
                int cc = col + c;
                if (rr >= 0 && rr < (int)grid.size() &&
                    cc >= 0 && cc < (int)grid[rr].size()) {
                    grid[rr][cc] = '?'; // prévisualisation
                }
            }
        }
    }

    // afficher la grille
    for (const auto& line : grid) {
        for (auto cell : line) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

void RendererCLI::displayTile(const Tile& tile) const {
    const auto& shape = tile.getShape();
    for (const auto& row : shape) {
        for (int cell : row) {
            std::cout << (cell ? "█" : " ") << " ";
        }
        std::cout << "\n";
    }
}

void RendererCLI::displayQueue(const TileQueue& queue) const {
    const auto& tiles = queue.getTiles();  // ✅ maintenant ça compile
    std::cout << "\n--- Tuiles en attente ---\n";
    int count = 0;
    for (const auto& tile : tiles) {
        std::cout << "Tuile #" << ++count << ":\n";
        displayTile(tile);
        std::cout << "\n";
    }
}
