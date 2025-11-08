#ifndef TILE_H
#define TILE_H

#include <vector>

class Board; // forward declaration

class Tile {
private:
    std::vector<std::vector<int>> shape;
    int width, height;

public:
    Tile(const std::vector<std::vector<int>>& shape);
    void rotate();
    void flip();
    bool canPlace(const Board& board, int row, int col) const;

    int getWidth() const;
    int getHeight() const;
    const std::vector<std::vector<int>>& getShape() const;
};

#endif
