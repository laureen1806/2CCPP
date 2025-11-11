#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "player.hpp"
#include "board.hpp"       // <-- Assure que Board est défini
#include "tileQueue.hpp"

class Game {
private:
    std::vector<Player> players;
    Board* board;           // OK car Board est défini
    TileQueue queue;
    int currentRound;

public:
    Game(int nbPlayers);
    void initializeTiles(int nbPlayers);
    void initGame();
    void playRound();
    void endGame();
    Player getWinner();
    void placeStone();
    void robTile(Player& thief);

};

#endif
