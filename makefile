SRC := src
BUILD := build
SOURCES := main.o $(BUILD)/obj/matrix.o $(BUILD)/obj/nn.o
CC := cc

all: $(BUILD)/obj/$(SOURCES)
	@echo Compiling main program: $^
	$(CC) -o $(BUILD)/run $^ 

debug: $(BUILD)/obj/$(SOURCES)
	@echo Compiling main program: $^
	@echo \*\*\* DEBUGGING
	$(CC) -DDEBUG -o $(BUILD)/run $^ 

$(BUILD)/obj/main.o: $(SRC)/main.c
	$(CC) -c -o $@ $<

$(BUILD)/obj/matrix.o: $(SRC)/Matrix/Matrix.c $(SRC)/Matrix/Matrix.h $(SRC)/Matrix/config.h
	@echo Compiling obj file and placing in: $@
	$(CC) -c -o $@ $<

$(BUILD)/obj/nn.o: $(SRC)/nn/nn.c $(SRC)/nn/nn.h
	$(CC) -c -o $@ $<
