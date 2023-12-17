PROJECT_NAME = enigma

CC = gcc
CFLAGS = -Wall -Wextra -Wstrict-prototypes -std=c99
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# set up modules 
MODULES = enigma/rotor enigma/plugboard enigma/reflector enigma helper cli

# set up source files
SRC = $(foreach module, $(MODULES), $(wildcard $(SRC_DIR)/$(module)/*.c)) $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

UNITY_DIR = libraries/Unity
UNITY_SRC = $(wildcard $(UNITY_DIR)/src/*.c)

TEST_DIR = test

TEST_SRC = $(foreach module, $(MODULES), $(wildcard $(TEST_DIR)/$(module)/*.c)) $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRC))
TEST_BIN = $(BIN_DIR)/test



#############################################

all: release

release: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(foreach module, $(MODULES), $(OBJ_DIR)/$(module))
	$(CC) $(CFLAGS) -c -o $@ $<

# debug target, maybe use debug flags instead of manipulating CFLAGS
debug: CFLAGS += -DDEBUG -g
debug: $(PROJECT_NAME)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(PROJECT_NAME)
	./$(BIN_DIR)/$(PROJECT_NAME)

test: CFLAGS += -DTEST -I$(UNITY_DIR)/src
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(UNITY_SRC) $(OBJ : $(OBJ_DIR)/main.o=)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(foreach module, $(MODULES), $(OBJ_DIR)/$(module))
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(UNITY_DIR)/src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(foreach module, $(MODULES), $(OBJ_DIR)/$(module))
	$(CC) $(CFLAGS) -c -o $@ $<



.PHONY: all clean debug run test

