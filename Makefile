CC = gcc

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

MODULES = enigma math

SRC = $(foreach module, $(MODULES), $(wildcard $(SRC_DIR)/$(module)/*.c)) $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: enigma
enigma: $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(foreach module, $(MODULES), $(OBJ_DIR)/$(module))
	$(CC) $(CFLAGS) -c -o $@ $<

# debug target, maybe use debug flags instead of manipulating CFLAGS
debug: CFLAGS += -DDEBUG -g
debug: enigma

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean debug