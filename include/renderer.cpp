// renderer.cpp
#include "../src/rendererCLI.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

static std::string ansiColor(const std::string& name) {
    if (name == "Red")     return "\x1b[31m";
    if (name == "Blue")    return "\x1b[34m";
    if (name == "Green")   return "\x1b[32m";
    if (name == "Yellow")  return "\x1b[33m";
    if (name == "Magenta") return "\x1b[35m";
    if (name == "Cyan")    return "\x1b[36m";
    if (name == "Orange")  return "\x1b[38;5;208m";
    if (name == "Purple")  return "\x1b[38;5;93m";
    if (name == "Teal")    return "\x1b[38;5;30m";
    return "\x1b[0m"; // reset
}
static const char* RESET = "\x1b[0m";

static std::string colorByPlayerId(const std::vector<Player>& players, int pid) {
    auto it = std::find_if(players.begin(), players.end(),
                           [&](const Player& p){ return p.getId() == pid; });
    return (it != players.end()) ? ansiColor(it->getColor()) : "";
}

void RendererCLI::displayBoard(const Board& board,
                               const std::vector<Player>& players) const {
    const int n = board.getSize();
    std::cout << "   ";
    for (int c = 0; c < n; ++c) std::cout << char('A' + (c % 26)) << " ";
    std::cout << "\n";

    for (int r = 0; r < n; ++r) {
        std::cout << char('A' + (r % 26)) << "  ";
        for (int c = 0; c < n; ++c) {
            const Cell& cell = board.at(r, c);
            if (cell.getTerrain() == Terrain::Stone) {
                std::cout << "# ";
            } else if (cell.getTerrain() == Terrain::Bonus) {
                std::cout << "* ";
            }else if (cell.isGrass()) {
                int pid = cell.getPlayerId();
                std::string color = colorByPlayerId(players, pid); // ✅ correction
                std::cout << color << "■ " << RESET;
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}


void RendererCLI::displayBoardWithPreview(const Board& board,
                                          const std::vector<Player>& players,
                                          const Tile& tile,
                                          int row, int col,
                                          const Player& currentPlayer) const
{
    const int n = board.getSize();

    std::cout << "   ";
    for (int c = 0; c < n; ++c) std::cout << char('A' + (c % 26)) << " ";
    std::cout << "\n";

    for (int r = 0; r < n; ++r) {
        std::cout << char('A' + (r % 26)) << "  ";
        for (int c = 0; c < n; ++c) {
            const Cell& cell = board.at(r, c);

            bool isPreview = false;
            const auto& shape = tile.getShape();
            if (!shape.empty()) {
                int sh = (int)shape.size();
                int sw = (int)shape[0].size();
                if (r >= row && r < row + sh &&
                    c >= col && c < col + sw &&
                    shape[r - row][c - col] == 1) {
                    isPreview = true;
                }
            }

            if (isPreview) {
                // ✅ Utiliser la couleur du joueur courant
                std::string color = ansiColor(currentPlayer.getColor());
                std::cout << color << "? " << RESET;
            }
            else if (cell.getTerrain() == Terrain::Stone) {
                std::cout << "# ";
            }
            else if (cell.getTerrain() == Terrain::Bonus) {
                std::cout << "* ";
            }
            else if (cell.isGrass()) {
                int pid = cell.getPlayerId();
                std::string color = colorByPlayerId(players, pid); // ✅ correction
                std::cout << color << "■ " << RESET;
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

void RendererCLI::displayTile(const Tile& tile) const {
    const auto& shape = tile.getShape();
    if (shape.empty()) {
        std::cout << "(tuile vide)\n";
        return;
    }
    for (const auto& row : shape) {
        for (int cell : row) {
            std::cout << (cell ? "█" : ".") << " ";
        }
        std::cout << "\n";
    }
}

void RendererCLI::displayQueue(const TileQueue& queue) const {
    const auto& tiles = queue.getTiles();
    std::cout << "\n--- Tuiles en attente ---\n";
    int count = 0;
    for (const auto& tile : tiles) {
        std::cout << "Tuile #" << ++count << ":\n";
        displayTile(tile);
        std::cout << "\n";
    }
}
