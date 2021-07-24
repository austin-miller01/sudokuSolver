# Compiler to use.
CC := g++
# Compilation flags.
CFLAGS := -c -g -Wall -Werror -Wpedantic --std=c++11
# Linker flags.
LFLAGS := -g
# Source code directory.
SRC := ./src
# Object code directory.
OBJ := ./obj
# Test code directory
TEST := ./tests

# main - interactive matrix manipulation utility
main: $(OBJ)/main.o $(OBJ)/matrix.o
	$(CC) $(LFLAGS) $(OBJ)/main.o $(OBJ)/matrix.o -o main

$(OBJ)/main.o: $(SRC)/main.cpp $(SRC)/matrix.hpp
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/matrix.o: $(SRC)/matrix.cpp $(SRC)/matrix.hpp
	$(CC) $(CFLAGS) $(SRC)/matrix.cpp -o $(OBJ)/matrix.o

# test
test:
	./test.sh

.PHONY: clean doc

# Remove object files and executable to ensure next make is entire.
clean:
	rm -rf $(OBJ)/*.o main

# Generate HTML documentation.
doc:
	doxygen doxyfile
