
all: main

main: main.o fnd.o joystick.o
	gcc -o main main.o fnd.o joystick.o -lwiringPi

joystick.o: joystick.c
	gcc -c joystick.c -lwiringPi

main.o: main.c
	gcc -c main.c -lwiringPi

fnd.o: fnd.c
	gcc -c fnd.c -lwiringPi


clean:
	rm -rf *.o main
