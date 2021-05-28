compile:
	clear
	gcc main.c libs/*.c `pkg-config --libs --cflags gtk+-3.0`

run:
	clear
	./a.out

emacs:
	clear
	emacs *.c libs/* &
