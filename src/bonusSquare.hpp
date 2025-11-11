#ifndef BONUS_SQUARE_HPP
#define BONUS_SQUARE_HPP

// Définition de l'énumération BonusType
enum class BonusType { NONE, EXCHANGE, STONE, ROBBERY };

// Forward declarations pour éviter les dépendances circulaires
class Player;
class Game;

class BonusSquare {
private:
    BonusType type;
    int row, col;

public:
    BonusSquare(BonusType type, int row, int col);
    void apply(Player& player, Game& game);

    BonusType getType() const;
    int getRow() const;
    int getCol() const;
};

#endif
