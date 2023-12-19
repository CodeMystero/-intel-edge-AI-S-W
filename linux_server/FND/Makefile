
all: main

main: keypad.o main.o fnd.o
	gcc -o main keypad.o main.o fnd.o -lwiringPi

keypad.o: keypad.c
	gcc -c keypad.c -lwiringPi

main.o: main.c
	gcc -c main.c -lwiringPi

fnd.o: fnd.c
	gcc -c fnd.c -lwiringPi


clean:
	rm -rf *.o main
