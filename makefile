SRC := src
BUILD := build
OBJ := $(BUILD)/obj
CC := cc

# Should be using this for the wildcard definition in 'build' rule -- not workgin
#objs := $(OBJ)/$(wildcard *.o)

build: $(OBJ)/*.o
	@echo Searching object directory for build files: $(OBJ)/$(objs)
	$(CC) $^ -o $(BUILD)/run

$(OBJ)/main.o: $(SRC)/main.c
	@echo Compiling main file
	$(CC) -c -o $@ $<

$(OBJ)/matrix.o: src/Matrix/Matrix.c src/Matrix/Matrix.h src/Matrix/config.h
	@echo Compiling Matrix library:  $<
	$(CC) -c -o $@ $<

$(OBJ)/nn.o: src/nn/nn.c src/nn/nn.h
	@echo Compiling neural network library: $<
	$(CC) -c -o $@ $<
