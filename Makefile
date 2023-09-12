PROJECT_NAME = skeleton

CC = gcc
CFLAGS = -Wall -Wextra -Wstrict-prototypes -pedantic -std=c99
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# set up modules
MODULES = example_module

# set up source files
SRC = $(foreach module, $(MODULES), $(wildcard $(SRC_DIR)/$(module)/*.c)) $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# set up unity testing framework
UNITY_PATH = libraries/Unity/src
UNITY_SRC = $(wildcard $(UNITY_PATH)/*.c)

TEST_DIR = test
TESTS = $(wildcard $(TEST_DIR)/src/*.c)

#############################################

all: release

release: CFLAGS += -Werror -O3
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

# unity testing framework
test: CFLAGS += -g
test: $(TESTS) $(filter-out $(OBJ_DIR)/main.o, $(OBJ))
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(UNITY_PATH) -o $(BIN_DIR)/$@ $^ $(UNITY_SRC)

run_test: test
	./$(BIN_DIR)/test

.PHONY: all clean debug run test
