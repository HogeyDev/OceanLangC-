CC = g++
LD = ld
CCFLAGS = -Wall -Werror -Wpedantic -I./src/include
LDFLAGS = 
SRCDIR = src
OBJDIR = lib
BUILDDIR = build

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS = $(call rwildcard,$(SRCDIR),*.cpp)          
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

.PHONY: clean

all: $(OBJS) link run
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo COMPILING $^
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -c $^ -o $@

link:
	@echo LINKING
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/main $(OBJS)

run:
	./build/main example/main.ocn

clean:
	rm build/main
	rm lib/*.o