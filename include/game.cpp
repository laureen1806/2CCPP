#include "../src/game.hpp"
#include "../src/board.hpp"
#include "../src/tileFactory.hpp"
#include "../src/rendererCLI.hpp"
#include "../src/inputManager.hpp"
#include "../src/player.hpp"
#include <algorithm>
#include <random>
#include <cmath>
#include <iostream>

Game::Game(int nbPlayers) : currentRound(0) {
    if (nbPlayers < 2) {
        std::cerr << "Il faut au moins 2 joueurs.\n";
        nbPlayers = 2;
    }

    int size = (nbPlayers <= 4) ? 20 : 30;
    board = std::make_unique<Board>(size);

    // Construire les joueurs
    players.clear();
    players.reserve(nbPlayers);
    for (int i = 0; i < nbPlayers; ++i) {
        std::string color = (i % 2 == 0) ? "Red" : "Blue";
        players.emplace_back("Joueur" + std::to_string(i + 1), color, i);
    }

    // Mélanger l’ordre des joueurs
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(players.begin(), players.end(), gen);

    initializeTiles(nbPlayers);
}

void Game::endGame() {
    std::cout << "\n=== Fin de partie ===\n";
    RendererCLI renderer;
    renderer.displayBoard(*board);

    Player winner = getWinner();
    std::cout << "Vainqueur : " << winner.getName() << "\n";
}

Player Game::getWinner() const {
    if (players.empty()) {
        std::cerr << "Aucun joueur — impossible de déterminer le vainqueur.\n";
        return Player("N/A", "None", -1);
    }

    int bestSquare = -1, bestGrass = -1;
    const Player* winner = nullptr;

    for (const auto& p : players) {
        int sq = p.calculateLargestSquare(*board);
        int grass = p.countGrassCells(*board);
        if (sq > bestSquare || (sq == bestSquare && grass > bestGrass)) {
            bestSquare = sq;
            bestGrass = grass;
            winner = &p;
        }
    }
    return winner ? *winner : Player("N/A", "None", -1);
}

void Game::initializeTiles(int nbPlayers) {
    int totalTiles = static_cast<int>(std::round(10.67 * nbPlayers));
    auto all = TileFactory::getAllTiles();
    if (all.empty()) {
        std::cerr << "Aucune tuile disponible.\n";
        tileQueue.clear();
        return;
    }

    std::vector<Tile> shuffled = all;
    std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937{std::random_device{}()});

    int take = std::min(totalTiles, static_cast<int>(shuffled.size()));
    tileQueue.assign(shuffled.begin(), shuffled.begin() + take);
}

void Game::placeStartingTile(Player& player) {
    RendererCLI renderer;
    InputManager input;

    // Tuile de départ 1x1
    Tile startTile(std::vector<std::vector<int>>{{1}});

    bool placed = false;
    while (!placed) {
        std::cout << "\n=== Placement initial de " << player.getName() << " ===\n";
        renderer.displayBoard(*board);

        std::cout << "Choisis une case (row col) pour ta tuile de départ : ";
        auto [r, c] = input.getCoordinates();

        int n = board->getSize();
        if (r < 0 || r >= n || c < 0 || c >= n) {
            std::cout << "Position invalide.\n";
            continue;
        }

        if (!board->at(r, c).isEmpty()) {
            std::cout << "Case déjà occupée, choisis une autre.\n";
            continue;
        }

        board->placeTile(startTile, player, r, c);
        player.setBase(r, c);
        placed = true;
    }
}

void Game::playTurn(Player& player) {
    if (tileQueue.empty()) {
        std::cout << "Pas de tuiles à jouer.\n";
        return;
    }

    Tile currentTile = tileQueue.front();
    tileQueue.pop_front();

    RendererCLI renderer;
    InputManager input;

    int previewRow = 0, previewCol = 0;
    bool validated = false;

    while (!validated) {
        std::cout << "\n=== Tour de " << player.getName() << " ===\n";
        renderer.displayBoardWithPreview(*board, players, currentTile, previewRow, previewCol);

        std::cout << "\nCommandes disponibles :\n";
        std::cout << "M row col : Déplacer la tuile\n";
        std::cout << "R         : Rotation 90° horaire\n";
        std::cout << "FH        : Flip horizontal\n";
        std::cout << "FV        : Flip vertical\n";
        std::cout << "V         : Valider le placement\n";
        std::cout << "Q         : Quitter le tour\n";

        std::string cmd = input.getCommand();

        if (cmd == "R") currentTile.rotate();
        else if (cmd == "FH") currentTile.flipH();
        else if (cmd == "FV") currentTile.flipV();
        else if (cmd == "M") {
            auto [row, col] = input.getCoordinates();
            int n = board->getSize();
            if (row >= 0 && row < n && col >= 0 && col < n) {
                previewRow = row;
                previewCol = col;
            } else {
                std::cout << "Position invalide.\n";
            }
        }
        else if (cmd == "V") {
            if (currentTile.canPlace(*board, previewRow, previewCol, player)) {
                board->placeTile(currentTile, player, previewRow, previewCol);
                validated = true;
            } else {
                std::cout << "Placement impossible.\n";
            }
        }
        else if (cmd == "Q") {
            std::cout << "Tour passé.\n";
            break;
        }
    }
}

void Game::playRound() {
    // Phase de placement initial au premier round
    if (currentRound == 0) {
        for (auto& player : players) {
            placeStartingTile(player);
        }
    }

    // Tours normaux
    for (auto& player : players) {
        playTurn(player);
        if (tileQueue.empty()) break;
    }

    currentRound++;
}
