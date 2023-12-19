#include "keypad.h"



const int _R[4] = {4,17,27,18};
const int _C[4] = {25,8,7,1};

char key_pad[4][4] = {{'1','2','3','+'},
           				 {'4','5','6','-'},
           				 {'7','8','9','*'},
           				 {'=','0','#','/'}};

char value = 'a';

void read_keypad(void){
	for(int i = 0; i <4;i++){
		digitalWrite(_C[i],HIGH);
		for(int j = 0; j <4; j++){
			if(digitalRead(_R[j]) == HIGH)value = key_pad[j][i];
		}
		digitalWrite(_C[i],LOW);
	}
}

void pin_mode(){
	for(int i = 0; i<4;i++){
		pinMode(_C[i],OUTPUT);
		pinMode(_R[i],INPUT);
	}
}

void pin_pupd(){
	for(int i = 0; i <4; i++)pullUpDnControl(_R[i],PUD_DOWN);

}
