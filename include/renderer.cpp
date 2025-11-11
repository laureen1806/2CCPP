// renderer.cpp
#include "../src/rendererCLI.hpp"
#include <iostream>
#include <vector>

void RendererCLI::displayBoard(const Board& board) const {
    const int n = board.getSize();
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
            else if (cell.isGrass()) ch = char('0' + (cell.getPlayerId() % 10));
            std::cout << ch << " ";
        }
        std::cout << "\n";
    }
}

void RendererCLI::displayBoardWithPreview(const Board& board,
                                          const std::vector<Player>& /*players*/,
                                          const Tile& tile,
                                          int row, int col) const
{
    const int n = board.getSize();

    // Build temp grid from board
    std::vector<std::vector<char>> tempGrid(n, std::vector<char>(n, '.'));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            const Cell& cell = board.at(r, c);
            char ch = '.';
            if (cell.getTerrain() == Terrain::Stone) ch = '#';
            else if (cell.getTerrain() == Terrain::Bonus) ch = '*';
            else if (cell.isGrass()) ch = char('0' + (cell.getPlayerId() % 10));
            tempGrid[r][c] = ch;
        }
    }

    // Overlay tile shape safely
    const auto& shape = tile.getShape();
    if (!shape.empty()) {
        const int sh = static_cast<int>(shape.size());
        const int sw = static_cast<int>(shape[0].size()); // assume rectangular; validate below

        // Validate rectangular shape (avoid segfault on jagged shapes)
        for (int rr = 1; rr < sh; ++rr) {
            if (static_cast<int>(shape[rr].size()) != sw) {
                std::cerr << "Tile shape rows have inconsistent widths. Aborting preview.\n";
                // fall back to no overlay
                goto render_only;
            }
        }

        for (int tr = 0; tr < sh; ++tr) {
            for (int tc = 0; tc < sw; ++tc) {
                if (shape[tr][tc] == 1) {
                    const int rr = row + tr;
                    const int cc = col + tc;
                    if (rr >= 0 && rr < n && cc >= 0 && cc < n) {
                        tempGrid[rr][cc] = '?';
                    }
                }
            }
        }
    }

render_only:
    // Render labeled grid
    std::cout << "   ";
    for (int c = 0; c < n; ++c) std::cout << char('A' + (c % 26)) << " ";
    std::cout << "\n";
    for (int r = 0; r < n; ++r) {
        std::cout << char('A' + (r % 26)) << "  ";
        for (int c = 0; c < n; ++c) {
            std::cout << tempGrid[r][c] << " ";
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
