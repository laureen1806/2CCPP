#include "../includes/tileQueue.hpp"

// Vérifie si la file est vide
bool TileQueue::empty() const {
    return queue.empty();
}

// Taille actuelle
size_t TileQueue::size() const {
    return queue.size();
}

// Accès à la première tuile
std::vector<Tile> TileQueue::peekNext(int count) const {
    std::vector<Tile> result;
    for (int i = 0; i < count && i < static_cast<int>(queue.size()); ++i) {
        result.push_back(queue[i]);
    }
    return result;
}

void TileQueue::pushBack(const Tile& tile) {
    queue.push_back(tile);
}
// Retire et renvoie la première tuile
Tile TileQueue::getNextTile() {
    Tile t = queue.front();
    queue.pop_front();
    return t;
}

// Retire et renvoie la tuile à un index précis
Tile TileQueue::takeAt(int index) {
    Tile t = queue[index];
    queue.erase(queue.begin() + index);
    return t;
}

// Initialise la file avec un sous-ensemble de tuiles
void TileQueue::assign(std::vector<Tile>::iterator begin, std::vector<Tile>::iterator end) {
    queue.assign(begin, end);
}

void TileQueue::clear() {
    queue.clear();
}

