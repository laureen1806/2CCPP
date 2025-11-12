#include "board.hpp"
#include "game.hpp"
#include "tileFactory.hpp"
#include "rendererCLI.hpp"
#include "inputManager.hpp"
#include "player.hpp"
#include <iostream>
#include <vector>

int main() {
    // Créer une partie avec 2 joueurs
    Game game(2);

    // Premier round = placement des tuiles de départ
    game.playRound();

    // Boucle de jeu : continuer jusqu’à la fin
    while (true) {
        game.playRound();
        // Condition de fin : plus de tuiles ou autre logique interne
        if (game.getBoard().getSize() == 0) { // exemple, adapte selon ta logique
            break;
        }
    }

    // Fin de partie
    game.endGame();
    return 0;
}
