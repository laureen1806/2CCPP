#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>       // pour std::unique_ptr
#include "player.hpp"
#include "board.hpp"
#include "tileQueue.hpp"

class Game {
private:
    std::vector<Player> players;          // liste des joueurs
    std::unique_ptr<Board> board;         // gestion mémoire sûre
    TileQueue tileQueue;                  // file de tuiles
    int currentRound;                     // numéro du tour

public:
    // Constructeur : crée le plateau et les joueurs
    Game(int nbPlayers);

    bool hasTiles() const;

    // Initialisation complète de la partie
    void initGame();

    // Joue un round complet (tous les joueurs jouent une fois)
    void playRound();

    // Logique de fin de partie (scores, affichage, etc.)
    void endGame();

    // Détermine le vainqueur
    Player getWinner() const;

    // Génère et mélange les tuiles
    void initializeTiles(int nbPlayers);

    // Joue le tour d’un joueur
    void playTurn(Player& player);

    void placeStartingTile(Player& player);

    // Accesseurs utiles
    Board& getBoard() { return *board; }
    const std::vector<Player>& getPlayers() const { return players; }
};

#endif
