all: debug

debug:
	nasm -g -f elf64 main.asm -o main.o
	ld -m elf_x86_64 main.o -o main.out -e main
	rm main.o
	gdb ./main.out

run:
	nasm -f elf64 main.asm -o main.o
	ld -m elf_x86_64 main.o -o main.out -e main
	rm main.o
	./main.out
