#include "board.hpp"
#include "game.hpp"
#include "tileFactory.hpp"
#include "rendererCLI.hpp"
#include "inputManager.hpp"
#include "player.hpp"
#include <iostream>
#include <limits>

int main() {
    int nbPlayers = 0;
    while (true) {
        std::cout << "Nombre de joueurs (2 à 9) : ";
        std::cin >> nbPlayers;
        if (std::cin.fail() || nbPlayers < 2 || nbPlayers > 9) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "⛔ Entrée invalide. Réessaie.\n";
        } else {
            break;
        }
    }

    Game game(nbPlayers);

    // Premier round = placement des tuiles de départ
    game.playRound();

    // ✅ Boucle principale : continue tant qu’il reste des tuiles
    while (game.hasTiles()) {
        game.playRound();
    }

    game.endGame();
    return 0;
}
