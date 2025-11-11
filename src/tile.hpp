#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

class Board;

class Tile {
private:
    std::vector<std::vector<int>> shape; // matrice binaire représentant la forme
    int width;
    int height;

public:
    // Constructeur
    Tile(const std::vector<std::vector<int>>& shape);

    void rotate();
    void flip();

    bool canPlace(const Board& board, int row, int col, int playerId) const;

    // Getters
    int getWidth() const;
    int getHeight() const;
    const std::vector<std::vector<int>>& getShape() const;
};

#endif
