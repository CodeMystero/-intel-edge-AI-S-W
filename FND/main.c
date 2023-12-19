#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#include "keypad.h"
#include "fnd.h"
#include <sys/shm.h>
#include <signal.h>
#include <sys/wait.h>

int flag_cnt = 0;
int setFloor = 0;

void intIsr();
void int_container(int);

int main(){

	int shmid;
	int *currentFloor;

	shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}

	currentFloor = shmat(shmid, NULL, 0);
	
	wiringPiSetupGpio();
	setPinMode();
	pin_pupd();
	pin_mode();

	for(int i = 0; i<4;i++){
		 wiringPiISR(_R[i],INT_EDGE_RISING,&intIsr);
	}

	while(1){
		read_keypad();
		
		if(flag_cnt == 1){
			int_container(atoi(&value));
			flag_cnt = 0;
			printf("%d\n", setFloor);
			delay(300);
		}

		displayFND10(*(currentFloor));
		
		if(value == '/'){
			pid_t pid = fork();
			switch(pid){
				case 0:
					while(1){
						sleep(1);
						printf("set >> %d, cur >> %d\n",setFloor, *currentFloor);
						if((*currentFloor)<setFloor){
							(*currentFloor)++;
						}else if((*currentFloor)>setFloor){
							(*currentFloor)--;
						}else{
							printf("child process ended\n");
							exit(EXIT_SUCCESS);
							//kill(0, SIGTERM);
						}
					}
					break;
				default:
					while(1){
						displayFND10(*currentFloor);
						if((*currentFloor) == setFloor){
							break;
						}
					}
					value = 'a';
               flag_cnt = 0;
               setFloor = 0;
					break;
			}
		}
	}
	return 0;
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


