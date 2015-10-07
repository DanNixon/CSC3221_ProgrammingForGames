OBJ_DIR = obj
BIN_DIR = bin

SRC_DIR = src
INC_DIR = inc
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_FILES:.cpp=.o))

TEST_DIR = test
TEST_FILES := $(shell find $(TEST_DIR) -name '*.h')
TEST_SRC = $(TEST_DIR)/tests.cpp
TEST_BIN = $(BIN_DIR)/tests


all: clean directories $(OBJECTS) tests

clean:
	rm -rf $(TEST_SRC)
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -c $< -o $@

run_tests: tests
	./$(TEST_BIN) -v

tests: directories $(OBJECTS)
	cxxtestgen -o $(TEST_SRC) --error-printer $(TEST_FILES)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -o $(TEST_BIN) $(TEST_SRC) $(OBJECTS)
