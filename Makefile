
all: mysl

mysl: mysl.h mysl.c mycurses.h mycurses.c
	gcc -Wall -o mysl mysl.c mycurses.c

clean:
	rm mysl
