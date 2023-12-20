#include "fnd.h"

const int DIG1 = 26;
const int A = 19;
const int F = 13;
const int DIG2 = 6;
const int DIG3 = 5;
const int B = 22;
const int DIG4 = 24;
const int G = 23;
const int C = 12;
const int DP = 16;
const int D = 20;
const int E = 21;

const int leds[12] = {21, 20, 16, 12, 24, 23,\
                      22, 5, 6, 13, 19, 26};
const int digits[4] = {26, 6, 5, 24};

void displayFND10 (int src){

   int digit[4];

   digit[0] = (src/1000)%10;
   digit[1] = (src/100)%10;
   digit[2] = (src/10)%10;
   digit[3] = src%10;

   for(int i = 0;i<4;i++){
      digitalOnOff(i+1,i,i-1,i-2);
      displayNumber(digit[i]);
      delayMicroseconds(5000);
   }
}


void displayFND16 (int src){

   int digit[4];

   digit[0] = (src/4096)%16;
   digit[1] = (src/256)%16;
   digit[2] = (src/16)%16;
   digit[3] = src%16;

   for(int i = 0;i<4;i++){
      digitalOnOff(i+1,i,i-1,i-2);
      displayNumber(digit[i]);
      delayMicroseconds(5000);
   }
}

void setPinMode(void){
   for(int i = 0; i <12; i++){
      pinMode(leds[i],OUTPUT);
   }
}

void digitalOnOff(int src1, int src2, int src3, int src4){

   int srcs[4] = {src1, src2, src3, src4};
   for(int i = 0;i<4;i++){
      if(srcs[i] == 1) digitalWrite(digits[i], HIGH);
      else digitalWrite(digits[i],LOW);
   }
}

void displayNumber(int selector){

   switch(selector){
      case 0:
         digitalWrite(A,LOW);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,LOW);
         digitalWrite(E,LOW);
         digitalWrite(F,LOW);
         digitalWrite(G,HIGH);
         digitalWrite(DP,HIGH);
         break;
      case 1:
         digitalWrite(A,HIGH);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,HIGH);
         digitalWrite(E,HIGH);
         digitalWrite(F,HIGH);
         digitalWrite(G,HIGH);
         digitalWrite(DP,HIGH);
         break;
      case 2:
         digitalWrite(A,LOW);
         digitalWrite(B,LOW);
         digitalWrite(C,HIGH);
         digitalWrite(D,LOW);
         digitalWrite(E,LOW);
         digitalWrite(F,HIGH);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 3:
         digitalWrite(A,LOW);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,LOW);
         digitalWrite(E,HIGH);
         digitalWrite(F,HIGH);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 4:
         digitalWrite(A,HIGH);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,HIGH);
         digitalWrite(E,HIGH);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 5:
         digitalWrite(A,LOW);
         digitalWrite(B,HIGH);
         digitalWrite(C,LOW);
         digitalWrite(D,LOW);
         digitalWrite(E,HIGH);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 6:
         digitalWrite(A,LOW);
         digitalWrite(B,HIGH);
         digitalWrite(C,LOW);
         digitalWrite(D,LOW);
         digitalWrite(E,LOW);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 7:
         digitalWrite(A,LOW);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,HIGH);
         digitalWrite(E,HIGH);
         digitalWrite(F,HIGH);
         digitalWrite(G,HIGH);
         digitalWrite(DP,HIGH);
         break;
      case 8:
         digitalWrite(A,LOW);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,LOW);
         digitalWrite(E,LOW);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 9:
         digitalWrite(A,LOW);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,LOW);
         digitalWrite(E,HIGH);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 10:
         digitalWrite(A,LOW);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,HIGH);
         digitalWrite(E,LOW);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 11:
         digitalWrite(A,HIGH);
         digitalWrite(B,HIGH);
         digitalWrite(C,LOW);
         digitalWrite(D,LOW);
         digitalWrite(E,LOW);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 12:
         digitalWrite(A,LOW);
         digitalWrite(B,HIGH);
         digitalWrite(C,HIGH);
         digitalWrite(D,LOW);
         digitalWrite(E,LOW);
         digitalWrite(F,LOW);
         digitalWrite(G,HIGH);
         digitalWrite(DP,HIGH);
         break;
      case 13:
         digitalWrite(A,HIGH);
         digitalWrite(B,LOW);
         digitalWrite(C,LOW);
         digitalWrite(D,LOW);
         digitalWrite(E,LOW);
         digitalWrite(F,HIGH);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 14:
         digitalWrite(A,LOW);
         digitalWrite(B,HIGH);
         digitalWrite(C,HIGH);
         digitalWrite(D,LOW);
         digitalWrite(E,LOW);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      case 15:
         digitalWrite(A,LOW);
         digitalWrite(B,HIGH);
         digitalWrite(C,HIGH);
         digitalWrite(D,HIGH);
         digitalWrite(E,LOW);
         digitalWrite(F,LOW);
         digitalWrite(G,LOW);
         digitalWrite(DP,HIGH);
         break;
      default:
         digitalWrite(A,HIGH);
         digitalWrite(B,HIGH);
         digitalWrite(C,HIGH);
         digitalWrite(D,HIGH);
         digitalWrite(E,HIGH);
         digitalWrite(F,HIGH);
         digitalWrite(G,HIGH);
         digitalWrite(DP,HIGH);
         break;

   }
}






