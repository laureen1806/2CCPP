#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <string>
#include <utility>

class InputManager {
public:
    std::string getCommand() const;
    std::pair<int,int> getCoordinates() const;
    char getRotationChoice() const;
};

#endif
