#ifndef TILE_FACTORY_HPP
#define TILE_FACTORY_HPP

#include "tile.hpp"
#include <vector>

class TileFactory {
public:
    static const std::vector<Tile>& getAllTiles(); // Accès aux 96 tuiles
};

#endif