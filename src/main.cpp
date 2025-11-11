#include "board.hpp"
#include "game.hpp"
#include "tileFactory.hpp"
#include "rendererCLI.hpp"
#include "inputManager.hpp"
#include "player.hpp"

int main() {
    Board board(10);
    RendererCLI renderer;
    InputManager input;

    // Création des joueurs
    std::vector<Player> players = {
        Player("Alice", "Red", 0),
        Player("Bob", "Blue", 1)
    };

    // Génération des tuiles
    auto tiles = TileFactory::getAllTiles();
    Tile currentTile = tiles[0];

    int previewRow = 0, previewCol = 0;
    bool validated = false;

    while (!validated) {
        std::cout << "\n=== Tour de " << players[0].getName() << " ===\n";

        renderer.displayBoardWithPreview(board, players, currentTile, previewRow, previewCol);

        std::cout << "\nCommandes disponibles :\n";
        std::cout << "M row col : Déplacer la tuile en prévisualisation\n";
        std::cout << "R         : Rotation 90° horaire\n";
        std::cout << "FH        : Flip horizontal\n";
        std::cout << "FV        : Flip vertical\n";
        std::cout << "V         : Valider le placement\n";
        std::cout << "Q         : Quitter le tour\n";

        std::string cmd = input.getCommand();

        if (cmd == "R") {
            currentTile.rotate();
        } else if (cmd == "FH") {
            currentTile.flipH();
        } else if (cmd == "FV") {
            currentTile.flipV();
        } else if (cmd == "M") {
            auto [row, col] = input.getCoordinates();
            previewRow = row;
            previewCol = col;
        } else if (cmd == "V") {
            if (currentTile.canPlace(board, previewRow, previewCol)) {
                board.placeTile(currentTile, players[0], previewRow, previewCol);
                validated = true;
            } else {
                std::cout << "Placement impossible, réessaie.\n";
            }
        } else if (cmd == "Q") {
            std::cout << "Tour passé.\n";
            break;
        }
    }

    renderer.displayBoard(board);  // 👈 correction : 1 seul argument

    return 0;
}
