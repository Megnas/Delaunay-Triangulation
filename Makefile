CC = g++
CFLAGS = -std=c++23 -fPIC
LIBS = -lSDL2
BIN = bin/
SRC = src/
MODULES = main pointGenerator
LIB_MODULES = delaunayTriangulation line2 triangle vector2
OBJS = $(addprefix $(BIN), $(addsuffix .o, $(MODULES)))
LIB_OBJS = $(addprefix $(BIN), $(addsuffix .o, $(LIB_MODULES)))
DEPS=$(wildcard $(SRC)*.hpp)

.PHONY: clean run lib

run: all
	LD_LIBRARY_PATH=$(BIN) ./$(BIN)triangulation

all: lib $(BIN)triangulation

lib: $(BIN)libmdt.so

$(BIN)triangulation: $(OBJS) $(BIN)libmdt.so
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS) -Lbin -lmdt

$(BIN)%.o: $(SRC)%.cpp $(DEPS) | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)libmdt.so: $(LIB_OBJS)
	$(CC) -shared $^ -o $@

$(BIN):
	mkdir $(BIN)

clean:
	rm -rf $(BIN)
