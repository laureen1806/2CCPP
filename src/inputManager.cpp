#include "../includes/inputManager.hpp"
#include <iostream>

// Récupère une commande utilisateur
std::string InputManager::getCommand() const {
    std::string cmd;
    std::cout << "Entrez une commande: ";
    std::cin >> cmd;
    return cmd;
}

// Récupère des coordonnées
std::pair<int, int> InputManager::getCoordinates() {
    std::string rowStr, colStr;
    int row = -1, col = -1;

    while (true) {
        std::cout << "Entrez la ligne et la colonne (ex: B D ou 1 3) : ";
        std::cin >> rowStr >> colStr;

        auto toIndex = [](const std::string& s) -> int {
            if (s.size() == 1 && std::isalpha(s[0])) {
                return std::toupper(s[0]) - 'A';  // A=0, B=1, etc.
            }
            try {
                return std::stoi(s);
            } catch (...) {
                return -1;
            }
        };

        row = toIndex(rowStr);
        col = toIndex(colStr);

        if (row >= 0 && col >= 0) break;

        std::cout << "⛔ Mouvement invalide, réessaie.\n";
    }

    return {row, col};
}

// Récupère un choix de rotation/flip
char InputManager::getRotationChoice() const {
    char choice;
    std::cout << "Rotation (R) ou Flip (F): ";
    std::cin >> choice;
    return choice;
}
