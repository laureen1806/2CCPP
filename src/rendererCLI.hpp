#ifndef RENDERER_H
#define RENDERER_H

#include "board.h"
#include "player.h"
#include "tile_queue.h"

class RendererCLI {
public:
    void displayBoard(const Board& board) const;
    void displayPlayerStatus(const Player& player) const;
    void displayQueue(const TileQueue& queue) const;
};

#endif
