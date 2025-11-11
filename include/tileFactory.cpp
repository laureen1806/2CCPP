#include "tileFactory.hpp"
#include "tile.hpp"
#include <vector>

static std::vector<Tile> allTiles = {
    // 1-carré
    Tile(std::vector<std::vector<int>>{{1}}),

    // 2-lignes
    Tile(std::vector<std::vector<int>>{{1,1}}),
    Tile(std::vector<std::vector<int>>{{1},{1}}),

    // 3-lignes
    Tile(std::vector<std::vector<int>>{{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1},{1},{1}}),

    // 4-lignes
    Tile(std::vector<std::vector<int>>{{1,1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1},{1},{1},{1}}),

    // 2x2 carré
    Tile(std::vector<std::vector<int>>{{1,1},{1,1}}),

    // L-shapes
    Tile(std::vector<std::vector<int>>{{1,0},{1,0},{1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1},{0,1},{1,1}}),
    Tile(std::vector<std::vector<int>>{{1,1},{1,0},{1,0}}),
    Tile(std::vector<std::vector<int>>{{1,1},{0,1},{0,1}}),

    // T-shapes
    Tile(std::vector<std::vector<int>>{{1,1,1},{0,1,0}}),
    Tile(std::vector<std::vector<int>>{{0,1},{1,1},{0,1}}),
    Tile(std::vector<std::vector<int>>{{0,1,0},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1,0},{1,1},{1,0}}),

    // Z-shapes
    Tile(std::vector<std::vector<int>>{{1,1,0},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1,1},{1,1,0}}),
    Tile(std::vector<std::vector<int>>{{1,0},{1,1},{0,1}}),
    Tile(std::vector<std::vector<int>>{{0,1},{1,1},{1,0}}),

    // S-shapes
    Tile(std::vector<std::vector<int>>{{0,1,1},{1,1,0}}),
    Tile(std::vector<std::vector<int>>{{1,1,0},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1},{1,1},{1,0}}),
    Tile(std::vector<std::vector<int>>{{1,0},{1,1},{0,1}}),

    // U-shapes
    Tile(std::vector<std::vector<int>>{{1,0,1},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1,1},{0,1},{1,1}}),

    // Cross
    Tile(std::vector<std::vector<int>>{{0,1,0},{1,1,1},{0,1,0}}),

    // Diagonals
    Tile(std::vector<std::vector<int>>{{1,0},{0,1}}),
    Tile(std::vector<std::vector<int>>{{0,1},{1,0}}),

    // Hooks
    Tile(std::vector<std::vector<int>>{{1,1},{0,1}}),
    Tile(std::vector<std::vector<int>>{{1,1},{1,0}}),
    Tile(std::vector<std::vector<int>>{{1,0},{1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1},{1,1}}),

    // Big L
    Tile(std::vector<std::vector<int>>{{1,0,0},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,0,1},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,1},{1,0,0}}),
    Tile(std::vector<std::vector<int>>{{1,1,1},{0,0,1}}),

    // Big T
    Tile(std::vector<std::vector<int>>{{1,1,1},{0,1,0},{0,1,0}}),
    Tile(std::vector<std::vector<int>>{{0,1,0},{1,1,1},{0,1,0}}),

    // Big Z
    Tile(std::vector<std::vector<int>>{{1,1,0},{0,1,1},{0,0,1}}),
    Tile(std::vector<std::vector<int>>{{0,0,1},{0,1,1},{1,1,0}}),

    // Big S
    Tile(std::vector<std::vector<int>>{{0,1,1},{1,1,0},{1,0,0}}),
    Tile(std::vector<std::vector<int>>{{1,0,0},{1,1,0},{0,1,1}}),

    // 3x3 blocks
    Tile(std::vector<std::vector<int>>{{1,1,1},{1,0,1},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,1},{1,1,1},{1,1,1}}),

    // Asymmetric
    Tile(std::vector<std::vector<int>>{{1,1,0},{0,1,0},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1,1},{0,1,0},{1,1,0}}),

    // Snake
    Tile(std::vector<std::vector<int>>{{1,0},{1,1},{0,1},{0,1}}),
    Tile(std::vector<std::vector<int>>{{0,1},{1,1},{1,0},{1,0}}),

    // Long shapes
    Tile(std::vector<std::vector<int>>{{1,1,1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1},{1},{1},{1},{1}}),

    // Complex
    Tile(std::vector<std::vector<int>>{{1,1,0},{1,1,1},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1,1},{1,1,1},{1,1,0}}),

    // Variants
    Tile(std::vector<std::vector<int>>{{1,0,1},{0,1,0},{1,0,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,0},{0,1,0},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1,1},{0,1,0},{1,1,0}}),
    Tile(std::vector<std::vector<int>>{{1,0,0},{1,1,0},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,0,1},{0,1,1},{1,1,0}}),
    Tile(std::vector<std::vector<int>>{{1,0,1},{1,1,1},{1,0,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,1},{1,0,1},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,0},{1,0,1},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1,1},{1,0,1},{1,1,0}}),
    Tile(std::vector<std::vector<int>>{{1,0,1},{0,1,0},{1,0,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,1},{0,1,0},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1,0,1},{1,1,1},{0,1,0}}),
    Tile(std::vector<std::vector<int>>{{0,1,0},{1,1,1},{1,0,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,0},{0,1,0},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,1,1},{0,1,0},{1,1,0}}),
    Tile(std::vector<std::vector<int>>{{1,0,0},{1,1,0},{0,1,1}}),
    Tile(std::vector<std::vector<int>>{{0,0,1},{0,1,1},{1,1,0}}),
    Tile(std::vector<std::vector<int>>{{1,1,1},{1,0,0},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,1},{0,0,1},{1,1,1}}),
    Tile(std::vector<std::vector<int>>{{1,1,1},{0,1,0},{1,1,1}})
};

const std::vector<Tile>& TileFactory::getAllTiles() {
    return allTiles;
}