#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <iostream>

class Board; // Forward declaration

class Tile {
private:
    std::vector<std::vector<int>> shape; // matrice binaire représentant la forme
    int width;
    int height;

public:
    // Constructeur sécurisé
    Tile(const std::vector<std::vector<int>>& shape);

    // Transformations
    void rotate();   // rotation 90° horaire
    void flipH();    // symétrie horizontale
    void flipV();    // symétrie verticale

    // Vérification placement
    bool canPlace(const Board& board, int row, int col) const;

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::vector<std::vector<int>> getShape() const {
        return shape;
    }


    // Affichage console
    void print() const;
};

#endif
