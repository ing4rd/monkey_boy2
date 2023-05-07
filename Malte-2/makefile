CC := g++
FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Weffc++ -g
LIB := -lsfml-window -lsfml-graphics -lsfml-system

# Dir
SRC = src
OBJ = obj
INC = header

# Variables
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SOURCES))
EXECUTABLE = monkey_boy2.0

# Rules
$(EXECUTABLE): $(OBJECTS) | dir
	@$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(OBJ)/%.o: $(SRC)/%.cpp | dir
	@$(CC) $(FLAGS) -c -o $@ $<

# Commands
all: $(EXECUTABLE)

dir:
	@mkdir -p $(OBJ)

clean:
	@rm -rf $(OBJ)/*.o $(EXECUTABLE)

