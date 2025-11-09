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
    int row, col;
    std::cout << "Entrez la ligne et la colonne: ";
    std::cin >> row >> col;
    return {row, col};
}

// Récupère un choix de rotation/flip
char InputManager::getRotationChoice() const {
    char choice;
    std::cout << "Rotation (R) ou Flip (F): ";
    std::cin >> choice;
    return choice;
}
