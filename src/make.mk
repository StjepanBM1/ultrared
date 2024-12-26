CC=g++
CF=-O3 -lSDL2

override BIN := 0
override CPP := $(shell find ./src -type f -name '*.cpp')
override OBJ := $(CPP:.cpp=.o)

.PHONY: all
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(CF)

%.o: %.cpp
	$(CC) -c $< -o $@ -O3

.PHONY: clean
clean:
	rm $(BIN) $(OBJ)
