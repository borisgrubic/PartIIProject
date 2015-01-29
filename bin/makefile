CC = g++
DEFAULT_WARNINGS = -Wall -Wextra -Werror -Wno-sign-compare -Wno-unused-result -Wno-unused-parameter -Wno-error=type-limits -Wno-error=unused-but-set-variable -Wno-inline -fno-strict-aliasing -Wno-unused-local-typedefs -Wno-unused-value
DEFAULT_WARNINGS_ALL = -Wall -Wextra -Werror
CFLAGS = -std=c++11 -O3

DIRS = ../src/types/ ../src/utils/ ../src/core/
SOURCES = $(foreach d, $(DIRS), $(wildcard $(d)*.cpp) )
OBJECTS = $(SOURCES:.cpp=.o)

TEST_DIRS = ../test/core/ ../test/types/ ../test/utils/ ../test/
TEST_SOURCES = $(foreach d, $(TEST_DIRS), $(wildcard $(d)*.cpp) )
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_TARGET = testAll

all: $(OBJECTS)

test: $(TEST_TARGET) $(TEST_OBJECTS) $(OBJECTS)
	./$(TEST_TARGET)
	
$(TEST_TARGET): $(TEST_OBJECTS) $(OBJECTS)
	$(CC) $(notdir $(TEST_OBJECTS)) $(notdir $(OBJECTS)) -g -o $(TEST_TARGET)

.cpp.o:
	$(CC) $(DEFAULT_WARNINGS_ALL) $(CFLAGS) $< -g -c -o $(notdir $@)

clear:
	rm -f $(notdir $(OBJECTS)) && \
	rm -f $(notdir $(TEST_OBJECTS)) && \
	rm -f testAll
