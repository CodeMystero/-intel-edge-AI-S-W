
all: main

main: keypad.o main.o
	gcc -o main keypad.o main.o -lwiringPi

keypad.o: keypad.c
	gcc -c keypad.c -lwiringPi

pwm_v1.o: main.c
	gcc -c main.c -lwiringPi

clean:
	rm -rf *.o main
