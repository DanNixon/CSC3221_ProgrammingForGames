TEST_DIR = 'test/'
TEST_FILES := $(shell find $(TEST_DIR) -name '*.h')

clean:
	test -f tests.cpp & rm tests.cpp
	test -f tests & rm tests

all: tests

run_tests: tests
	./runner

tests: tests.cpp
	$(CXX) -o $@ $<

tests.cpp: $(TEST_FILES)
	cxxtestgen -o $@ --error-printer $^
