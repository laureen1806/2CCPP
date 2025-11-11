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

    // Accès à la première tuile
    Tile& peek();

    // Accès à une tuile donnée sans la retirer
    Tile& peek(int index);

    // Retire et renvoie la première tuile
    Tile getNextTile();

    // Retire et renvoie la tuile à l’index spécifié
    Tile takeAt(int index);

    // Remplit la file à partir d’un vecteur
    void assign(std::vector<Tile>::iterator begin, std::vector<Tile>::iterator end);
};

#endif
