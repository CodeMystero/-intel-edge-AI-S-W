#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

const int _R[4] = {12, 16, 20, 21};
const int _C[4] = {26, 19, 13, 6};

void pin_mode();
void pin_pupd();
void read_keypad(const int, int);
int chaIntId(char);
void intIsr();
void int_container(double);
void interInit(void);

char key_pad[4][4] = {{'1','2','3','+'},
                      {'4','5','6','-'},
                      {'7','8','9','*'},
                      {'=','0','#','/'}};

char value = 'a';
char operater_1;
double num_cnt = 0;
int flag_cnt = 0;
double snum[2] = {0,};

int main(){
   wiringPiSetupGpio();
   pin_mode();
   pin_pupd();
   interInit();
   while(1){

      double src_temp;

      for(int i = 0;i <4;i++)read_keypad(_C[i],i);
      delay(200);

      if(chaIntId(value) == 0){
         src_temp = atoi(&value);
         if(flag_cnt == 1){
            int_container(src_temp);
            flag_cnt = 0;
            printf("%.1f\r",num_cnt);
            fflush(NULL);
         }
      }else if(chaIntId(value) == 1){
         printf("\n%c\n",value);
         fflush(NULL);
         snum[0] = num_cnt;
         num_cnt = 0;
         operater_1 = value;
      }else if(chaIntId(value) == 2){
         snum[1] = num_cnt;
         num_cnt = 0;

         switch(operater_1){
            case '+':
               printf("\n>> %.1f\n",snum[0]+snum[1]);
               break;
            case '/':
               printf("\n>> %.1f\n",snum[0]/snum[1]);
               break;
            case '*':
               printf("\n>> %.1f\n",snum[0]*snum[1]);
               break;
            case '-':
               printf("\n>> %.1f\n",snum[0]-snum[1]);
               break;
         }
      }
      value = 'a';
   }
}

void interInit(void){
   for(int i = 0; i<4;i++){
      wiringPiISR(_R[i],INT_EDGE_FALLING,&intIsr);
   }
}


void intIsr(void){
   flag_cnt = 1;
}

void int_container(double src){
   num_cnt = num_cnt*10 + src;
}

int chaIntId(char src){ // 0 if int, 1 if char

   if(src == '1'||src == '2'||src == '3'||src =='4'||src == '5'\
      ||src == '6'||src == '7'||src == '8'||src == '9'||src =='0'){
      return 0;
   }else if (src == '#'||src == '/'||src == '*'||src == '-'||src =='+'){
      return 1;
   }else if (src == '='){
      return 2;
   }
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
