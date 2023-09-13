CC = g++
CCFLAGS = -Wall -Werror -Wpedantic -I./src/include/

SRCFILES = $(shell find ./src/ | grep .cpp)

all: compile run test

compile: $(SRCFILES)
	$(CC) $(CCFLAGS) $(SRCFILES) -o build/main

run:
	./build/main example/main.ocn

test:
	./build/example/main
