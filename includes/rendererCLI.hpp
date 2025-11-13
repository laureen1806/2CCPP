#ifndef RENDERER_H
#define RENDERER_H

#include "board.hpp"
#include "player.hpp"
#include "tileQueue.hpp"


class RendererCLI {
public:
    void displayBoard(const Board& board,
                      const std::vector<Player>& players) const;
    void displayPlayerStatus(const Player& player) const;
    void displayQueue(const TileQueue& queue) const;

    void displayBoardWithPreview(const Board& board,
                             const std::vector<Player>& players,
                             const Tile& tile,
                             int row, int col,
                             const Player& currentPlayer) const;

    void displayTile(const Tile& tile) const;
};

#endif
