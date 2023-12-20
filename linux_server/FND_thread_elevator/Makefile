
all: main

main: keypad.o main.o fnd.o
	gcc -o main keypad.o main.o fnd.o -lwiringPi -pthread -lpthread

keypad.o: keypad.c
	gcc -c keypad.c -lwiringPi -D_REENTRANT

main.o: main.c
	gcc -c main.c -lwiringPi -D_REENTRANT

fnd.o: fnd.c
	gcc -c fnd.c -lwiringPi -D_REENTRAT


clean:
	rm -rf *.o main
