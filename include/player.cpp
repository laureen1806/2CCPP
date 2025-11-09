#include "../src/player.hpp"
#include "../src/board.hpp"
#include "../src/cell.hpp"
#include <algorithm> // pour std::min

Player::Player(const std::string& name, const std::string& color, int id)
    : name(name), color(color), id(id), coupons(1) {}

std::string Player::getName() const { return name; }
std::string Player::getColor() const { return color; }
int Player::getCoupons() const { return coupons; }
int Player::getId() const { return id; }

void Player::useCoupon() {
    if (coupons > 0) coupons--;
}

void Player::placeTile(Tile& tile) {
    territory.push_back(tile);
}

// Calcul du plus grand carré
int Player::calculateLargestSquare(const Board& board) const {
    int n = board.getSize();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    int best = 0;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            const Cell& cell = board.at(r, c);
            bool mine = cell.isGrass() && cell.getPlayerId() == this->getId();
            if (!mine) { dp[r][c] = 0; continue; }
            if (r == 0 || c == 0) dp[r][c] = 1;
            else dp[r][c] = 1 + std::min(std::min(dp[r-1][c], dp[r][c-1]), dp[r-1][c-1]);
            if (dp[r][c] > best) best = dp[r][c];
        }
    }
    return best;
}

// Comptage des cases en herbe
int Player::countGrassCells(const Board& board) const {
    int count = 0;
    for (int r = 0; r < board.getSize(); ++r) {
        for (int c = 0; c < board.getSize(); ++c) {
            const Cell& cell = board.at(r, c);
            if (cell.isGrass() && cell.getPlayerId() == this->getId()) ++count;
        }
    }
    return count;
}
