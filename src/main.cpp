#include "board.hpp"
#include "game.hpp"
#include "tileFactory.hpp"
#include "rendererCLI.hpp"
#include "inputManager.hpp"
#include "player.hpp"
#include <iostream>
#include <vector>

int main() {
    // Plateau carré de taille N
    const int N = 10;
    Board board(N);
    RendererCLI renderer;
    InputManager input;

    // Création des joueurs (au moins 2)
    std::vector<Player> players = {
        Player("Alice", "Red", 0),
        Player("Bob",   "Blue", 1)
    };

    // Génération des tuiles (file/collection de tuiles disponibles)
    auto tiles = TileFactory::getAllTiles();
    if (tiles.empty()) {
        std::cerr << "Aucune tuile disponible. Fin du programme.\n";
        return 1;
    }

    // État de partie
    int currentPlayerIndex = 0;
    int previewRow = 0, previewCol = 0;
    Tile currentTile = tiles.front();

    // Boucle de partie: continue tant qu'il reste des tuiles (ou selon votre condition de fin)
    while (!tiles.empty()) {
        Player& currentPlayer = players[currentPlayerIndex];

        // Affichage du tour + plateau avec prévisualisation
        std::cout << "\n=== Tour de " << currentPlayer.getName() << " ===\n";
        renderer.displayBoardWithPreview(board, players, currentTile, previewRow, previewCol);

        // Commandes
        std::cout << "\nCommandes disponibles :\n";
        std::cout << "M row col : Déplacer la tuile en prévisualisation\n";
        std::cout << "R         : Rotation 90° horaire\n";
        std::cout << "FH        : Flip horizontal\n";
        std::cout << "FV        : Flip vertical\n";
        std::cout << "V         : Valider le placement\n";
        std::cout << "Q         : Passer le tour\n";
        std::cout << "E         : Échanger la tuile (prendre la suivante)\n";
        std::cout << "D         : Afficher la tuile\n";

        std::string cmd = input.getCommand();

        if (cmd == "R") {
            currentTile.rotate();
            std::cout << "Rotation effectuée.\n";
        } else if (cmd == "FH") {
            currentTile.flipH();
            std::cout << "Flip horizontal effectué.\n";
        } else if (cmd == "FV") {
            currentTile.flipV();
            std::cout << "Flip vertical effectué.\n";
        } else if (cmd == "M") {
            auto [row, col] = input.getCoordinates();
            // Sécuriser la position de prévisualisation dans les bornes du plateau
            if (row < 0 || row >= N || col < 0 || col >= N) {
                std::cout << "Position invalide (" << row << ", " << col << ").\n";
            } else {
                previewRow = row;
                previewCol = col;
            }
        } else if (cmd == "D") {
            std::cout << "\nTuile actuelle:\n";
            renderer.displayTile(currentTile);
        } else if (cmd == "E") {
            // Échanger la tuile actuelle avec la suivante disponible
            tiles.erase(tiles.begin());
            if (tiles.empty()) {
                std::cout << "Plus de tuiles à échanger.\n";
            } else {
                currentTile = tiles.front();
                std::cout << "Tuile échangée.\n";
            }
        } else if (cmd == "V") {
            // Validation du placement: on place si possible
            if (currentTile.canPlace(board, previewRow, previewCol)) {
                board.placeTile(currentTile, currentPlayer, previewRow, previewCol);
                std::cout << "Tuile placée par " << currentPlayer.getName() << ".\n";

                // Retirer la tuile jouée et passer au joueur suivant
                tiles.erase(tiles.begin());
                if (tiles.empty()) {
                    std::cout << "Plus de tuiles disponibles. Fin de partie.\n";
                    break;
                }
                currentTile = tiles.front();
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

                // Réinitialiser la preview raisonnablement (par exemple 0,0)
                previewRow = 0;
                previewCol = 0;

            } else {
                std::cout << "Placement impossible, réessaie (déplace/rotation/flip).\n";
            }
        } else if (cmd == "Q") {
            std::cout << "Tour passé par " << currentPlayer.getName() << ".\n";
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        } else {
            std::cout << "Commande inconnue.\n";
        }

        // Afficher l'état courant du plateau après action
        renderer.displayBoard(board);
    }

    std::cout << "\n=== Plateau final ===\n";
    renderer.displayBoard(board);
    return 0;
}
