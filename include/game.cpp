#include "../src/game.hpp"
#include "../src/board.hpp"
#include "../src/tileFactory.hpp"
#include "../src/rendererCLI.hpp"
#include "../src/inputManager.hpp"
#include <algorithm>
#include <random>
#include <cmath>
#include <iostream>

Game::Game(int nbPlayers) : currentRound(0) {
    int size = (nbPlayers <= 4) ? 20 : 30;
    board = new Board(size);

    // TODO: construire les joueurs
    // Exemple : for (int i = 0; i < nbPlayers; ++i) players.emplace_back(i, "Joueur" + std::to_string(i+1));

    // Mélanger l’ordre des joueurs
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(players.begin(), players.end(), gen);

    initializeTiles(nbPlayers);
}

void Game::endGame() {
    // TODO: logique de fin de partie
}

Player Game::getWinner() {
    int bestSquare = -1, bestGrass = -1;
    Player* winner = nullptr;

    for (auto& p : players) {
        int sq = p.calculateLargestSquare(*board);   // 👈 correction
        int grass = p.countGrassCells(*board);       // 👈 correction
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

void Game::playTurn(Player& player) {
    Tile currentTile = tileQueue.front();
    tileQueue.erase(tileQueue.begin());

    RendererCLI renderer;
    InputManager input;

    int previewRow = 0, previewCol = 0;
    bool validated = false;

    while (!validated) {
        std::cout << "\n=== Tour de " << player.getName() << " ===\n";

        renderer.displayBoardWithPreview(*board, players, currentTile, previewRow, previewCol);

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
            if (currentTile.canPlace(*board, previewRow, previewCol)) {
                board->placeTile(currentTile, player, previewRow, previewCol);
                validated = true;
            } else {
                std::cout << "Placement impossible, réessaie.\n";
            }
        } else if (cmd == "Q") {
            std::cout << "Tour passé.\n";
            break;
        }
    }
}
