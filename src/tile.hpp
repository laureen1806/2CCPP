#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

class Board; // Forward declaration

class Tile {
private:
    std::vector<std::vector<int>> shape; // matrice binaire représentant la forme
    int width;
    int height;

public:
    // Constructeur
    Tile(const std::vector<std::vector<int>>& shape);

    // Transformations
    void rotate();   // rotation 90°
    void flip();     // symétrie horizontale/verticale

    // Vérification placement
    bool canPlace(const Board& board, int row, int col) const;

    // Getters
    int getWidth() const;
    int getHeight() const;
    const std::vector<std::vector<int>>& getShape() const;
};

#endif
