# Nom de l'exécutable
TARGET = game

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src

# Fichiers sources
SRC = $(wildcard include/*.cpp) $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o) src/main.o  # 👈 on ajoute main.o manuellement

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(TARGET)

# Compilation + exécution
run: all
	./$(TARGET)
