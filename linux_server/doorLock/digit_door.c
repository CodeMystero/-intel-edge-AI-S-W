#include <stdio.h>
#include <wiringPi.h>
#include "lcd1602.h"
#include <string.h>

const int _R[4] = {12, 16, 20, 21};
const int _C[4] = {26, 19, 13, 6}; 
const int LED = 23;
int input_flag = 0;

char password[4] = {'0','0','0','0'};
char uin[4] = {' ',' ',' ',' '};
int pos = 0;

void pin_mode();
void pin_pupd();
void read_keypad(const int, int);
void interInit();
void intIsr();
void user_input_arr(char*,int);
int arr_cmp(char*, char*);
void digit_reset();
void lineType(char*, int);


char key_pad[4][4] = {{'1','2','3','+'},
                      {'4','5','6','-'},
                      {'7','8','9','p'},
                      {'*','0','#','c'}};


char value = 'a';
char* title = "==Vitual door==";
char* door_opened = "** door open **";
char* door_closed = "* door closed *";
char* you_got = ">> New digits";
char* set_password = "New password :";
int main(){
   wiringPiSetupGpio();
   interInit();
   
	pinMode(LED, OUTPUT);

	xio = wiringPiI2CSetup(I2C_ADDR);
	lcd_init();
	lcdClear();

   pin_mode();
   pin_pupd();
   while(1){
   	lcdLoc(LINE1);
   	typeln(title);

		for(int i = 0;i <4;i++)read_keypad(_C[i],i);
      delay(50);

		if (uin[0] == '0' && uin[1] == '0'\
			 &&  uin[2] == '0' && uin[3] == '0'){ 
			 if (value == '#'){
			 	for(int i = 0; i<4 ; i++) password[i] = ' ';
			 	input_flag = 0;
			 	while(1){
					for(int i = 0;i <4;i++)read_keypad(_C[i],i);
					delay(50);
					if(value == '*') break;
					user_input_arr(password, input_flag);

					lineType(password, LINE2);
					lcdLoc(LINE1);
					typeln(set_password);
				}
				digit_reset();
			}
		}
		if (value == '*'){
			if(arr_cmp(password, uin)==1){
				digitalWrite(LED, 1);
				lcdLoc(LINE2);
				typeln(door_opened);
				digit_reset();
				input_flag = 0;
			}else{
				pos = 0;
				lcdClear();
				lcdLoc(LINE2);
				typeln(you_got);
				digit_reset();
				input_flag = 0;
			}
		
		}
		if (value == 'c'){ 
			digitalWrite(LED, 0);
			lcdLoc(LINE2);
			typeln(door_closed);
			input_flag = 0;
			delay(1000);
		}
	

		if (value == 'p'){
			lineType(password,LINE1);
			delay(1000);
		}

		user_input_arr(uin,input_flag);
 
      if(value != 'a' && value != '*'){
			lineType(uin, LINE2);
      }
      
      value = 'a';
   }
}
void lineType (char* arr, int line){

	lcdClear();
	lcdLoc(line);
	for(int i =0; i<4; i++){
		typeChar(arr[i]);
	}
	input_flag = 0;
}
void digit_reset(void){
	for(int i = 0;i <4; i++){
		uin[i] = ' ';
	}
}

int arr_cmp(char* src1, char* src2){
	int key=0;
	for(int i = 0; i<4; i++){
		if(src1[i] == src2[i]) key++;
	}
	if(key == 4)return 1;
	else return 0;
}

void user_input_arr(char *arr,int flag){
	if(flag == 1){
   	arr[pos++] =  value;
   	fflush(NULL);
   	input_flag = 0;
   	delay(10);
   	if (pos >3) pos = 0;
   }
}
void interInit(void){
	for(int i = 0; i < 4; i++){
		wiringPiISR(_R[i],INT_EDGE_FALLING,&intIsr);
	}
}

void intIsr(void){
	input_flag = 1; 
}

void read_keypad(const int c, const int col){
	digitalWrite(c, HIGH);
	for(int i = 0;i < 4;i++){
		if(digitalRead(_R[i]) == HIGH)value = key_pad[i][col];
	}
	digitalWrite(c, LOW);
}

void pin_mode(){
	for(int i = 0; i<4;i++){
		pinMode(_C[i],OUTPUT);
		pinMode(_R[i],INPUT);
	}
}

void pin_pupd(){
	for(int i = 0; i <4; i++)pullUpDnControl(_R[i], PUD_DOWN);
}
