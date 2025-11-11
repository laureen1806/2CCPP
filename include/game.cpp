#include "../src/game.hpp"
#include "../src/board.hpp"
#include "../src/tileFactory.hpp"
#include "../src/tileQueue.hpp"
#include "../src/bonusSquare.hpp"
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;

Game::Game(int nbPlayers) : currentRound(0) {
    initGame(); // initialise joueurs et tuiles

    // Boucle principale du jeu
    while (currentRound < 9 && !queue.empty()) {
        playRound(); // joue un round complet
    }

    endGame();
}

//Initialisations des joueurs, des tuiles et prépare la partie.
void Game::initGame() {
    cout << "\n=== Initialisation du jeu ===\n";

    int nbPlayers;
    cout << "Entrez le nombre de joueurs (2 à 6) : ";
    cin >> nbPlayers;
    while (nbPlayers < 2 || nbPlayers > 6) {
        cout << "Nombre invalide, réessayez : ";
        cin >> nbPlayers;
    }

    players.clear();

    // --- Création des joueurs ---
    for (int i = 0; i < nbPlayers; ++i) {
        string name, color;
        cout << "Nom du joueur " << (i + 1) << " : ";
        cin >> name;
        cout << "Couleur du joueur " << (i + 1) << " : ";
        cin >> color;

        players.emplace_back(name, color, i);
    }

    // --- Création du plateau ---
    int size = (nbPlayers <= 4) ? 20 : 30;
    board = new Board(size); 

    // --- Mélange de l’ordre de jeu ---
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(players.begin(), players.end(), gen);

    cout << "\nOrdre de jeu : ";
    for (auto& p : players) cout << p.getName() << " ";
    cout << "\n";

    // --- Initialisation de la file de tuiles ---
    initializeTiles(nbPlayers);

    cout << "Tuiles mélangées et prêtes. Début du jeu !\n";
}

//Place une pierre sur le plateau (bonus)
void Game::placeStone() {
    int r, c;
    cout << "Entrez la position pour placer la pierre (row col) : ";
    cin >> r >> c;

    if (board->isInside(r, c) && !board->at(r, c).isEmpty()) {
        board->at(r, c).setStone();
        cout << "Pierre placée en (" << r << ", " << c << ").\n";
    } else {
        cout << "Impossible de placer la pierre à cet endroit.\n";
    }
}

//Vol d’une tuile à un autre joueur.
void Game::robTile(Player& thief) {
    if (players.size() < 2) {
        cout << "Pas assez de joueurs pour voler.\n";
        return;
    }

    cout << "Choisissez la victime parmi :\n";
    for (auto& p : players) {
        if (p.getId() != thief.getId())
            cout << " - " << p.getId() << ": " << p.getName() << "\n";
    }

    int victimId;
    cout << "Entrez l'ID du joueur à voler : ";
    cin >> victimId;

    Player* victim = nullptr;
    for (auto& p : players) {
        if (p.getId() == victimId) {
            victim = &p;
            break;
        }
    }

    if (!victim) {
        cout << "Joueur invalide.\n";
        return;
    }

    if (victim->getTerritory().empty()) {
        cout << victim->getName() << " n'a aucune tuile à voler.\n";
        return;
    }

    // On prend la dernière tuile posée
    Tile stolen = victim->getTerritory().back();
    victim->removeLastTile();

    // Le voleur recoit la tuile qui vient d'etre volée
    thief.placeTile(stolen);
    cout << thief.getName() << " a volé une tuile à " << victim->getName() << " !\n";
}

void Game::endGame() {
    std::cout << "\n=== Phase finale : achat des tuiles 1x1 ===\n";

    for (auto& player : players) {
        int coupons = player.getCoupons();
        if (coupons <= 0) continue;

        std::cout << player.getName() << " possède " << coupons 
                  << " coupon(s). Souhaitez-vous acheter des tuiles 1x1 ? (y/n): ";

        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') continue;

        for (int i = 0; i < coupons; ++i) {
            player.useCoupon();
            Tile tile({{1}}); // tuile 1x1
            int r, c;
            std::cout << "Position pour la tuile 1x1 #" << (i + 1) << " : ";
            std::cin >> r >> c;

            if (tile.canPlace(*board, r, c, player.getId())) {
                board->placeTile(tile, player, r, c);
                player.placeTile(tile);
            } else {
                std::cout << "Impossible de placer la tuile 1x1 ici.\n";
            }
        }
    }

    // Calcul du gagnant
    Player winner = getWinner();
    std::cout << "\n=== Résultat final ===\n";
    std::cout << "Le gagnant est : " << winner.getName() << "\n";
}

Player Game::getWinner() {
    int bestSquare = -1, bestGrass = -1;
    Player* winner = nullptr;

    for (auto& p : players) {
        int sq = p.calculateLargestSquare(*board);
        int grass = p.countGrassCells(*board);
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

    vector<Tile> shuffled = all;
    shuffle(shuffled.begin(), shuffled.end(), std::mt19937{std::random_device{}()});

    queue.assign(shuffled.begin(), shuffled.begin() + totalTiles);
}

void BonusSquare::apply(Player& player, Game& game) {
    switch (type) {
        case BonusType::EXCHANGE:
            player.addCoupon();
            cout<< player.getName() << " gagne un coupon d'échange !\n";
            break;

        case BonusType::STONE:
            cout << player.getName() << " place une pierre.\n";
            game.placeStone();
            break;

        case BonusType::ROBBERY:
            cout << player.getName() << " vole une tuile à un autre joueur.\n";
            game.robTile(player);
            break;
    }
}

void Game::playRound() {
    std::cout << "\n=== Début du round " << (currentRound + 1) << " ===\n";

    for (auto& player : players) {
        if (queue.empty()) {
            std::cout << "Plus de tuiles disponibles !\n";
            break;
        }

        std::cout << "\n--- Tour de " << player.getName() << " ---\n";
        std::cout << "Coupons disponibles : " << player.getCoupons() << "\n";

        Tile tile = queue.peek(); // première tuile du queue
        bool usedCoupon = false;

        // Gestion de coupon d’échange
        if (player.getCoupons() > 0 && queue.size() >= 5) {
            char choice;
            std::cout << "Souhaitez-vous utiliser un coupon pour choisir une tuile parmi les 5 prochaines ? (y/n): ";
            std::cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                usedCoupon = true;
                player.useCoupon();

                // Affiche les 5 prochaines tuiles
                std::cout << "Voici les 5 prochaines tuiles :\n";
                for (int i = 0; i < 5 && i < queue.size(); ++i)
                    std::cout << " - Tuile #" << i << " (" 
                              << queue.peek(i).getWidth() << "x" 
                              << queue.peek(i).getHeight() << ")\n";

                int index;
                std::cout << "Choisissez le numéro de la tuile (0-4) : ";
                std::cin >> index;
                tile = queue.takeAt(index); // retire la tuile choisie
            } else {
                tile = queue.getNextTile();
            }
        } else {
            tile = queue.getNextTile();
        }

        // Demande position
        int r, c;
        std::cout << "Position de placement (row col) : ";
        std::cin >> r >> c;

        if (tile.canPlace(*board, r, c, player.getId())) {
            board->placeTile(tile,player, r, c);
            player.placeTile(tile);
            std::cout << "Tuile placée avec succès.\n";
        } else {
            std::cout << "Impossible de placer la tuile, elle est défaussée.\n";
        }
    }

    currentRound++;

    if (currentRound >= 9 || queue.empty()) {
        std::cout << "\n=== Fin des rounds ===\n";
        endGame();
    }
}
