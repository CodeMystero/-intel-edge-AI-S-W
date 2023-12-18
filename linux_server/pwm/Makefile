
all: main

main: keypad.o pwm_v1.o
	gcc -o main keypad.o pwm_v1.o -lwiringPi

keypad.o: keypad.c
	gcc -c keypad.c -lwiringPi

pwm_v1.o: pwm_v1.c
	gcc -c pwm_v1.c -lwiringPi

clean:
	rm -rf *.o main
