#include <io.h>
#include <delay.h>

int i=0;
const char number[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x80};
int hour=0,min=0,sec=0;
const int one_sec =250;
int reverse = 1;

void check(void){
        if(sec>59){
            min++;
            sec=0;
         }
         if(min>59){
            hour++;
            min=0;
         }
         if(hour>23){
            hour=0;
         }

          if(sec<0){
            min--;
            sec=59;
          }
          if(min<0){
            hour--;
            min=59;
          }
          if(hour<0){
            hour=23;
          }
      }

void show(int n){
    int temp;
    switch(n){
        case 0:
            temp = hour/10;
            PORTC=number[temp];
            break;
        case 1:
            temp = hour%10;
            PORTC=number[temp];
            break;
        case 2:
            PORTC=number[10];
            break;
        case 3:
            temp = min/10;
            PORTC=number[temp];
            break;
        case 4:
            temp = min%10;
            PORTC=number[temp];
            break;
        case 5:
            PORTC=number[10];
            break;
        case 6:
            temp=sec/10;
            PORTC=number[temp];
            break;
        case 7:
            temp = sec%10;
            PORTC=number[temp];
            break;
    }
}

void button(void){
      if(PINA.0==0){
            reverse = reverse * -1;
            if(reverse==-1){
                PORTB=0x01;
            }
            else{
                PORTB=0x00;
                }
            }
        if(PINA.1==0 && reverse==1){
            sec++;
        }
        if(PINA.1==0 && reverse==-1){
            sec--;
        }
        if(PINA.2==0 && reverse==1){
            min++;
        }
        if(PINA.2==0 && reverse==-1){
            min--;
        }
        if(PINA.3==0 && reverse==1){
            hour++;
        }
        if(PINA.3==0 && reverse==-1){
            hour--;
        }
         sec++;
   }

void main(void){
char seven_seg=0x01;
int seg_num=0;


DDRC=0xff;
DDRD=0xff;
PORTC=0xff;
DDRA=0x00;
PORTA=0xff;
DDRB=0xff;
PORTB=0x00;

for(i=0;;i++){

     PORTD=~seven_seg;
     seven_seg=seven_seg<<1;
     if(seven_seg==0x00){
        seven_seg=0x01;
     }

     if(seg_num>7){
        seg_num=0;
     }

      check();

     show(seg_num);

     seg_num++;
     delay_ms(4);


     if(i%one_sec==0){
        i=0;
        button();
    }
  }
 }

