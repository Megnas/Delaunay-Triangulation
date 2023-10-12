CC = g++
CFLAGS = -std=c++23
LIBS = -lSDL2
BIN = bin/
SRC = src/
MODULES = main delaunayTriangulation line2 triangle vector2 pointGenerator
OBJS = $(addprefix $(BIN), $(addsuffix .o, $(MODULES)))

.PHONY: init clean run purge

run: all
	./$(BIN)triangulation

all: $(BIN)triangulation

$(BIN)triangulation: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BIN)%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

init:
	mkdir bin

clean:
	rm -rf $(BIN)*.o $(BIN)triangulation

purge: clean
	rm -rf $(BIN)
