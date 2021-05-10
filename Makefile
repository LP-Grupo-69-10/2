compile:
	gcc -Wall main.c libs/*.c

run:
	./a.out

emacs:
	emacs main.c libs/* &
