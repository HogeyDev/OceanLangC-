CC = g++
CCFLAGS = -Wall -Werror -Wpedantic -I./src/include/ -g

SRCFILES = $(shell find ./src/ | grep .cpp)

all: compile run test

compile: $(SRCFILES)
	$(CC) $(CCFLAGS) $(SRCFILES) -o build/main

run:
	./build/main example/main.ocn -o example/main.out

test:
	./example/main.out

debug:
	gdb --args ./build/main example/main.ocn -o example/main.out