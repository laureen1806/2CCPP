#ifndef BONUS_SQUARE_HPP
#define BONUS_SQUARE_HPP

// Définition de l'énumération BonusType
enum class BonusType { NONE, EXCHANGE, STONE, ROBBERY };

// Forward declarations pour éviter les dépendances circulaires
class Player;
class Game;

class BonusSquare {
private:
    int row, col;
    BonusType type;

public:
    BonusSquare(int row, int col,BonusType type):  row(row), col(col), type(type){};
    void apply(Player& player, Game& game);

    
    int getRow() const;
    int getCol() const;
    BonusType getType() const;
};

#endif
