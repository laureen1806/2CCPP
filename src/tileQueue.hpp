#ifndef TILE_QUEUE_H
#define TILE_QUEUE_H

#include <queue>
#include "tile.hpp"

class TileQueue {
private:
    std::queue<Tile> tiles;

public:
    TileQueue();
    Tile getNextTile();
    Tile exchangeTile(int index);
    void refillQueue();
};

#endif
