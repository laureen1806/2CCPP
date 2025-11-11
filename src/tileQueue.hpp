#ifndef TILE_QUEUE_HPP
#define TILE_QUEUE_HPP

#include <vector>
#include "tile.hpp"

class TileQueue {
private:
    std::vector<Tile> tiles;

public:
    TileQueue() = default;

    // Remplir la queue avec une liste de tuiles
    template<typename Iter>
    void assign(Iter first, Iter last) {
        tiles.assign(first, last);
    }

    // Récupérer la première tuile
    Tile front() const {
        return tiles.front();
    }

    // Supprimer une tuile
    void erase(std::vector<Tile>::iterator pos) {
        tiles.erase(pos);
    }

    // Accès à begin()
    std::vector<Tile>::iterator begin() {
        return tiles.begin();
    }

    bool empty() const {
        return tiles.empty();
    }

    size_t size() const {
        return tiles.size();
    }

    const std::vector<Tile>& getTiles() const;
};

#endif
