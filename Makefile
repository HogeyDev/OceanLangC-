CC = g++
CCFLAGS = -Wall -Werror -Wpedantic -I ./src/include/ -g -std=c++20

SRCFILES = $(shell find ./src/ | grep .cpp)

all: compile run test

setup:
	mkdir -p build

compile: setup $(SRCFILES)
	$(CC) $(CCFLAGS) $(SRCFILES) -o build/main

run:
	./build/main example/main.ocn -o example/main.out

test:
	./example/main.out

debug: compile
	gdb --args ./build/main example/main.ocn -o example/main.out

bear:
	bear -- make
