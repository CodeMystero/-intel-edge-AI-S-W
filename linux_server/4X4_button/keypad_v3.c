 #include <stdio.h>
 #include <wiringPi.h>
 
 const int _R[4] = {12, 16, 20, 21};
 const int _C[4] = {26, 19, 13, 6};

void pin_mode();
void pin_pupd();
void read_keypad(const int, int);

char key_pad[4][4] = {{'1','2','3','+'},
                      {'4','5','6','-'},
                      {'7','8','9','*'},
                      {'=','0','#','/'}};

char value = 'a';

int main(){

   wiringPiSetupGpio();
   pin_mode();
   pin_pupd();
   while(1){

      for(int i = 0;i <4;i++)read_keypad(_C[i],i);
     delay(200);
      if(value != 'a')printf("%c\n",value);
       value = 'a';

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
