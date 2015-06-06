CFLAGS=-Wall -Wextra -std=c99 -O0 -ggdb
NASMFLAGS=-f elf64 -g -F DWARF
OBJS=ejecutame.o transformar.o

ejecutame: $(OBJS)

%.o: %.asm
	 nasm $(NASMFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f ejecutame
