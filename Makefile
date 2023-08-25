CC = gcc

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -O2

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# set up modules
MODULES = enigma math helper

# set up source files
SRC = $(foreach module, $(MODULES), $(wildcard $(SRC_DIR)/$(module)/*.c)) $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# set up unity testing framework
TEST_DIR = test
TESTS = $(wildcard $(TEST_DIR)/src/*.c)
UNITY_PATH = $(TEST_DIR)/unity
UNITY_SRC = $(wildcard $(UNITY_PATH)/*.c)

#############################################

all: enigma

enigma: $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(foreach module, $(MODULES), $(OBJ_DIR)/$(module))
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: enigma
	./$(BIN_DIR)/enigma

# unity testing framework and link to enigma
test: $(TESTS) $(filter-out $(OBJ_DIR)/main.o, $(OBJ))
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(UNITY_PATH) -o $(BIN_DIR)/$@ $^ $(UNITY_SRC) 

runtest: test
	./$(BIN_DIR)/test

# debug target, maybe use debug flags instead of manipulating CFLAGS
debug: CFLAGS += -DDEBUG -g
debug: enigma

.PHONY: all clean debug run test
