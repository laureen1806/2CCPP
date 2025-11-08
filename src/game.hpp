#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "board.h"
#include "tile_queue.h"

class Game {
private:
    std::vector<Player> players;
    Board board;
    TileQueue queue;
    int currentRound;

public:
    Game(int nbPlayers);
    void initGame();
    void playRound();
    void endGame();
    Player getWinner();
};

#endif
