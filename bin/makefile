CC = g++
DEFAULT_WARNINGS = -Wall -Wextra -Werror -Wno-sign-compare -Wno-unused-result -Wno-unused-parameter -Wno-error=type-limits -Wno-error=unused-but-set-variable -Wno-inline -fno-strict-aliasing -Wno-unused-local-typedefs -Wno-unused-value
DEFAULT_WARNINGS_ALL = -Wall -Wextra -Werror
CFLAGS = -std=c++11 -O3

DIRS = ../src/types/ ../src/utils/ ../src/core/
SOURCES = $(foreach d, $(DIRS), $(wildcard $(d)*.cpp) )
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS)

.cpp.o:
	$(CC) $(DEFAULT_WARNINGS_ALL) $(CFLAGS) $< -c -o $(notdir $@)

clear:
	rm $(notdir $(OBJECTS))
