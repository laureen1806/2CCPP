#ifndef TILE_QUEUE_HPP
#define TILE_QUEUE_HPP

#include <queue>
#include "tile.hpp"
#include <deque>
#include <vector>

class TileQueue {
private:
    std::deque<Tile> queue;
public:
    bool empty() const;
    size_t size() const;

    std::vector<Tile> peekNext(int count) const;
    void pushBack(const Tile& tile);

    // Retire et renvoie la première tuile
    Tile getNextTile();

    // Retire et renvoie la tuile à l’index spécifié
    Tile takeAt(int index);

    // Remplit la file à partir d’un vecteur
    void assign(std::vector<Tile>::iterator begin, std::vector<Tile>::iterator end);

    // Vide la file
    void clear();

    // avoir les prochaines tiles
    const std::deque<Tile>& getTiles() const {
    return queue;
    }   
};

#endif
