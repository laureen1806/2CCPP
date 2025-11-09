#include "../src/rendererCLI.hpp"
#include <iostream>

// Affiche le plateau
void RendererCLI::displayBoard(const Board& board) const {
    int n = board.getSize();
    std::cout << "   ";
    for (int c = 0; c < n; ++c) std::cout << char('A' + (c % 26)) << " ";
    std::cout << "\n";

    for (int r = 0; r < n; ++r) {
        std::cout << char('A' + (r % 26)) << "  ";
        for (int c = 0; c < n; ++c) {
            const Cell& cell = board.at(r, c);
            char ch = '.';
            if (cell.getTerrain() == Terrain::Stone) ch = '#';
            else if (cell.getTerrain() == Terrain::Bonus) ch = '*';
            else if (cell.isGrass()) ch = '0' + (cell.getPlayerId() % 10); // show player id digit
            std::cout << ch << " ";
        }
        std::cout << "\n";
    }
}

// Affiche l'état d'un joueur
void RendererCLI::displayPlayerStatus(const Player& player) const {
    std::cout << "Joueur: " << player.getName()
              << " | Couleur: " << player.getColor()
              << " | Coupons: " << player.getCoupons() << std::endl;
}

// Affiche la file de tuiles
void RendererCLI::displayQueue(const TileQueue& queue) const {
    std::cout << "=== File de tuiles ===" << std::endl;
    // TODO: afficher les tuiles disponibles
}

