TEST_DIR = 'test/'
TEST_FILES := $(shell find $(TEST_DIR) -name '*.h')

clean:
	rm -f tests
	rm -f tests.cpp

all: tests

run_tests: tests
	./tests

tests: tests.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

tests.cpp: $(TEST_FILES)
	cxxtestgen -o $@ --error-printer $^
