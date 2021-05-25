compile:
	gcc -Wall main.c libs/*.c

run:
	./a.out

emacs:
	emacs main.c libs/* &

interface:
	gcc -o t9 interface.c `pkg-config --libs --cflags gtk+-3.0`

draw:
	./t9
