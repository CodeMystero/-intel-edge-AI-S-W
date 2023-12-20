#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#include "keypad.h"
#include "fnd.h"
#include <sys/shm.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

int flag_cnt = 0;
int setFloor = 0;
int currentFloor = 0;

void intIsr();
void int_container(int);

void *displayFloor(void* arg);
void *countFloor(void* arg);

int main(){
		
	wiringPiSetupGpio();
	setPinMode();
	pin_pupd();
	pin_mode();

	pthread_t a_thread[2];
	void *test_result;

	for(int i = 0; i<4;i++){
		 wiringPiISR(_R[i],INT_EDGE_RISING,&intIsr);
	}

	while(1){
		
		read_keypad();
		
		if(flag_cnt == 1){
			int_container(atoi(&value));
			flag_cnt = 0;
			printf("%c\n", value);
			delay(300);
		}

		displayFND10(currentFloor);

		if(value == '/'){
			pthread_create(&a_thread[0], NULL,countFloor,NULL);
			pthread_create(&a_thread[1], NULL,displayFloor, NULL);

			pthread_join(a_thread[0],NULL);
			pthread_join(a_thread[1],NULL);

			setFloor = 0;
			value = 'a';
			flag_cnt = 0;
		}
	}
	return 0;
}
void *displayFloor(void* arg){
	while(1){
		displayFND10(currentFloor);
		if(currentFloor == setFloor) break;
	}
}

void *countFloor(void* arg){
	while(1){
		printf("set : %d, current : %d\n", setFloor, currentFloor);
		delayMicroseconds(200000);
		if(currentFloor<setFloor){
			(currentFloor)++;
		}else if(currentFloor>setFloor){
			(currentFloor)--;
		}else if (currentFloor == setFloor){
			break;
		}
	}
}

void intIsr(void){
	flag_cnt = 1;
}

void int_container(int src){
	if (value != '/'){
		setFloor = setFloor*10 + src;
		delay(200);
		if(setFloor > 9999) setFloor = 0;
	}
}


