#include <iostream>
#include "src/board.hpp"
#include "src/tile.hpp"
#include "src/player.hpp"
#include "src/rendererCLI.hpp"

int main() {
    // Initialisation du plateau 20x20
    Board board(20);

    // Création d’un joueur
    Player player("Laureen", "Vert", 0); // ID = 0

    // Création d’une tuile en forme de L
    std::vector<std::vector<int>> shape = {
        {1, 0},
        {1, 0},
        {1, 1}
    };
    Tile tile(shape);

    // Affichage de la tuile originale
    std::cout << "Tuile originale :\n";
    for (const auto& row : tile.getShape()) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }

    // Rotation de la tuile
    tile.rotate();
    std::cout << "\nTuile après rotation :\n";
    for (const auto& row : tile.getShape()) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }

    // Placement de la tuile sur le plateau à la position (5, 5)
    bool success = board.placeTile(tile, player, 5, 5);
    std::cout << "\nPlacement à (5,5) : " << (success ? "Réussi" : "Échec") << "\n";

    // Affichage du plateau
    RendererCLI renderer;
    renderer.displayBoard(board);

    // Calcul du plus grand carré pour le joueur
    int largestSquare = player.calculateLargestSquare(board);
    std::cout << "\nPlus grand carré de Laureen : " << largestSquare << "x" << largestSquare << "\n";

    // Nombre total de cases en herbe
    int grassCount = player.countGrassCells(board);
    std::cout << "Nombre total de cases en herbe : " << grassCount << "\n";

    return 0;
}
