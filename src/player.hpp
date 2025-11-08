#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "tile.h"

class Player {
private:
    std::string name;
    std::string color;
    std::vector<Tile> territory;
    int coupons;

public:
    Player(const std::string& name, const std::string& color);
    void placeTile(Tile& tile);
    void useCoupon();
    int calculateLargestSquare() const;

    std::string getName() const;
    std::string getColor() const;
    int getCoupons() const;
};

#endif
