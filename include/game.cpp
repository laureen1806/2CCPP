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
    if (nbPlayers > 9) {
        std::cerr << "Maximum 9 joueurs.\n";
        nbPlayers = 9;
    }

    // Taille du plateau : 20x20 pour 2–4 joueurs, 30x30 pour 5–9
    int size = (nbPlayers <= 4) ? 20 : 30;
    board = std::make_unique<Board>(size);

    // Palette de couleurs (jusqu’à 9 joueurs)
    const std::vector<std::string> palette = {
        "Red", "Blue", "Green", "Yellow", "Magenta",
        "Cyan", "Orange", "Purple", "Teal"
    };

    // Construire les joueurs avec saisie des noms
    players.clear();
    players.reserve(nbPlayers);

    for (int i = 0; i < nbPlayers; ++i) {
        std::string name;
        std::cout << "Entrez le nom du joueur " << (i + 1) << " : ";
        std::getline(std::cin >> std::ws, name);
        if (name.empty()) {
            name = "Joueur" + std::to_string(i + 1);
        }

        std::string color = palette[i % palette.size()];
        players.emplace_back(name, color, i);
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
    renderer.displayBoard(*board, players);

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
        renderer.displayBoard(*board, players);

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

    Tile currentTile = tileQueue.getNextTile(); // retire la première tuile
    RendererCLI renderer;
    InputManager input;

    int previewRow = 0, previewCol = 0;
    bool validated = false;

    while (!validated) {
        std::cout << "\n=== Tour de " << player.getName() << " ===\n";
        std::cout << "Coupons restants : " << player.getCoupons() << "\n\n";

        auto nextFive = tileQueue.peekNext(5);
        std::cout << "=== Prochaines tuiles dans la file ===\n";

        if (nextFive.empty()) {
            std::cout << "(aucune tuile restante)\n";
        } else {
            // Déterminer la hauteur maximale pour l'affichage côte à côte
            int maxRows = 0;
                for (const auto& t : nextFive)
                maxRows = std::max(maxRows, (int)t.getShape().size());

            // Pour chaque ligne de la tuile
            for (int r = 0; r < maxRows; ++r) {
                for (size_t i = 0; i < nextFive.size(); ++i) {
                    const auto& shape = nextFive[i].getShape();
                    if (r < (int)shape.size()) {
                        for (int cell : shape[r])
                            std::cout << (cell ? "■" : ".");
                    } else {
                        for (int k = 0; k < (int)shape[0].size(); ++k)
                            std::cout << " ";
                    }
                    std::cout << "   "; // espacement entre les tuiles
                }
                std::cout << "\n";
            }
        
            // Indiquer les indices sous les tuiles
            for (size_t i = 0; i < nextFive.size(); ++i)
                std::cout << "  (" << i + 1 << ")      ";
            std::cout << "\n";
        }
        std::cout << "\nTuile actuelle à placer :\n";
        currentTile.print(); 

        renderer.displayBoardWithPreview(*board, players, currentTile, previewRow, previewCol);

        std::cout << "\nCommandes disponibles :\n";
        std::cout << "M row col : Déplacer la tuile\n";
        std::cout << "R         : Rotation 90° horaire\n";
        std::cout << "FH        : Flip horizontal\n";
        std::cout << "FV        : Flip vertical\n";
        std::cout << "E i       : Échanger avec la tuile i (1-5) en utilisant un coupon\n";
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
        else if (cmd == "E") {
            if (player.getCoupons() <= 0) {
                std::cout << "Tu n’as plus de coupon pour échanger.\n";
                continue;
            }

            std::cout << "Choisis la tuile (1-5) à échanger : ";
            int idx;
            std::cin >> idx;
            if (idx < 1 || idx > 5 || idx > (int)tileQueue.size()) {
                std::cout << "Indice invalide.\n";
                continue;
            }

            Tile newTile = tileQueue.takeAt(idx - 1);
            player.useCoupon();
            std::cout << "Tuile échangée avec la tuile #" << idx << " !\n";
            currentTile = newTile;
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

bool Game::hasTiles() const {
    return !tileQueue.empty();
}


