compile:
	clear
	gcc -Wall main.c libs/*.c

run:
	clear
	./a.out

emacs:
	clear
	emacs main.c libs/* &

interface:
	clear
	gcc interface.c libs/*.c `pkg-config --libs --cflags gtk+-3.0`
	./a.out

gtk3:
	sudo apt-get install libgtk-3-dev
