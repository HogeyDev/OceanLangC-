all: main

CXX = clang++
override CXXFLAGS += -g -Wno-everything -Wall -Werror -Wpedantic

SRCS = $(shell find ./src/ | grep .cpp)
HEADERS = $(shell find ./src/ | grep .hpp)
HEADERS += $(shell find ./src/ | grep .h)

main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug