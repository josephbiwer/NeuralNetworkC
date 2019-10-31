SRC := src
BUILD := build
SOURCES := main.o $(BUILD)/obj/matrix.o $(BUILD)/obj/nn.o
CFLAGS ?=
CC := gcc

all: $(BUILD)/obj/$(SOURCES)
	@echo Compiling main program: $^
	$(CC) -o $(BUILD)/run $^ 

$(BUILD)/obj/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/obj/matrix.o: $(SRC)/Matrix/Matrix.c $(SRC)/Matrix/Matrix.h $(SRC)/Matrix/config.h
	@echo Compiling obj file and placing in: $@
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/obj/nn.o: $(SRC)/nn/nn.c $(SRC)/nn/nn.h
	$(CC) $(CFLAGS) -c -o $@ $<
