#include "../src/game.hpp"
#include "../src/board.hpp"
#include "../src/tileFactory.hpp"
#include <random>

Game::Game(int nbPlayers) : currentRound(0) {
    int size = (nbPlayers <= 4) ? 20 : 30;
    board = new Board(size); // if you chose Board* in game.hpp
    // build players...
    // randomize turn order
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(players.begin(), players.end(), gen);
}

void Game::endGame() {
    // compute winner using largest square, tie-break grass
}

Player Game::getWinner() {
    int bestSquare = -1, bestGrass = -1;
    Player* winner = nullptr;

    for (auto& p : players) {
        int sq = p.calculateLargestSquare(boardRef());
        int grass = p.countGrassCells(boardRef());
        if (sq > bestSquare || (sq == bestSquare && grass > bestGrass)) {
            bestSquare = sq;
            bestGrass = grass;
            winner = &p;
        }
    }
    return *winner;
}

void Game::initializeTiles(int nbPlayers) {
    int totalTiles = std::round(10.67 * nbPlayers);
    auto all = TileFactory::getAllTiles();

    std::vector<Tile> shuffled = all;
    std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937{std::random_device{}()});

    tileQueue.assign(shuffled.begin(), shuffled.begin() + totalTiles);
}