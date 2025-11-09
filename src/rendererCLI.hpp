#ifndef RENDERER_H
#define RENDERER_H

#include "board.hpp"
#include "player.hpp"
#include "tileQueue.hpp"

class RendererCLI {
public:
    void displayBoard(const Board& board) const;
    void displayPlayerStatus(const Player& player) const;
    void displayQueue(const TileQueue& queue) const;
};

#endif
