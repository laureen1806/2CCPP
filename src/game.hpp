#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "player.hpp"
#include "board.hpp"
#include "tileQueue.hpp"

class Game {
private:
    std::vector<Player> players;
    Board* board;           // pointeur vers le plateau
    TileQueue tileQueue;    // cohérent avec l’implémentation
    int currentRound;

public:
    Game(int nbPlayers);

    void initGame();
    void playRound();
    void endGame();
    Player getWinner();

    void initializeTiles(int nbPlayers);   // 👈 ajouté
    void playTurn(Player& player);         // 👈 ajouté
};

#endif
