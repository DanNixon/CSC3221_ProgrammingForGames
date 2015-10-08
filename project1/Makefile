OBJ_DIR = obj
BIN_DIR = bin

SRC_DIR = src
INC_DIR = inc
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_FILES:.cpp=.o))

TEST_DIR = test
TEST_FILES := $(shell find $(TEST_DIR) -name '*.h')
CXXTEST_SRC = $(TEST_DIR)/cxxtests.cpp
CXXTEST_BIN = $(BIN_DIR)/cxxtests
TEST_SRC = $(TEST_DIR)/Test.cpp
TEST_BIN = $(BIN_DIR)/tests


all: clean directories $(OBJECTS) cxxtest submission_tests

clean:
	rm -rf $(CXXTEST_SRC)
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -c $< -o $@

run_cxxtest: cxxtest
	./$(CXXTEST_BIN) -v

cxxtest: directories $(OBJECTS)
	cxxtestgen -o $(CXXTEST_SRC) --error-printer $(TEST_FILES)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -o $(CXXTEST_BIN) $(CXXTEST_SRC) $(OBJECTS)

run_submission_tests: submission_tests
	./$(TEST_BIN)

submission_tests: directories $(OBJECTS)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -o $(TEST_BIN) $(TEST_SRC) $(OBJECTS)
