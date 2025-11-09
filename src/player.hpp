#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "tile.hpp"

// Forward declaration pour éviter les inclusions circulaires
class Board;

class Player {
private:
    std::string name;
    std::string color;
    std::vector<Tile> territory;
    int coupons;
    int id;   // ← AJOUTÉ

public:
    // Constructeur
    Player(const std::string& name, const std::string& color, int id);

    // Gestion des tuiles
    void placeTile(Tile& tile);
    void useCoupon();

    // Calculs sur le territoire
    int calculateLargestSquare(const Board& board) const;
    int countGrassCells(const Board& board) const;

    // Getters
    std::string getName() const;
    std::string getColor() const;
    int getCoupons() const;
    int getId() const;   // ← AJOUTÉ
};

#endif
