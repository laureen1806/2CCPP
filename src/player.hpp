#ifndef PLAYER_HPP
#define PLAYER_HPP

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
    int id;
    int coupons;

    // 👇 Ajoute ces deux attributs pour mémoriser la base
    int baseRow = -1;
    int baseCol = -1;

public:
    // Constructeur
    Player(const std::string& name, const std::string& color, int id);

    // Gestion des tuiles
    void placeTile(Tile& tile);
    void useCoupon();

    // Gestion de la base de départ
    void setBase(int row, int col) {
        baseRow = row;
        baseCol = col;
    }

    std::pair<int,int> getBase() const {
        return {baseRow, baseCol};
    }

    bool hasBase() const {
        return baseRow != -1 && baseCol != -1;
    }

    // Calculs sur le territoire
    int calculateLargestSquare(const Board& board) const;
    int countGrassCells(const Board& board) const;

    // Getters
    std::string getName() const;
    std::string getColor() const;
    int getCoupons() const;
    int getId() const;
};

#endif
