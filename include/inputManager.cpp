#include "../src/inputManager.hpp"
#include <iostream>

// Récupère une commande utilisateur
std::string InputManager::getCommand() const {
    std::string cmd;
    std::cout << "Entrez une commande (P=placer, R=rotation, F=flip, E=échange, D=afficher): ";
    std::cin >> cmd;
    return cmd;
}

// Récupère des coordonnées
std::pair<int,int> InputManager::getCoordinates() const {
    std::string rowStr, colStr;
    std::cin >> rowStr >> colStr;

    auto toIndex = [](const std::string& s) -> int {
        if (s.size() == 1 && std::isalpha(s[0])) {
            return std::toupper(s[0]) - 'A'; // A=0, B=1, etc.
        }
        return std::stoi(s); // sinon, interpréter comme chiffre
    };

    int row = toIndex(rowStr);
    int col = toIndex(colStr);
    return {row, col};
}

// Récupère un choix de rotation/flip
char InputManager::getRotationChoice() const {
    char choice;
    std::cout << "Rotation (R) ou Flip (F): ";
    std::cin >> choice;
    return choice;
}
