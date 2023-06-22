  // ** Diretivas de Pré Processamento ** */
#include <string.h>
#include <stdlib.h>
#define Col_1 (RB4_bit)
#define Col_2 (RB5_bit)
#define Col_3 (RB6_bit)
#define Col_4 (RB7_bit)
#define La (RB0_bit)
#define Lb (RB1_bit)
#define Lc (RB2_bit)
#define Ld (RB3_bit)

char keypadPort at PORTB;

// Conexões do Módulo LCD
sbit LCD_RS at RD0_bit;
sbit LCD_EN at RD1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

char tecla(){
     char kp=0;
     do{ kp=Keypad_Key_Click(); }while(kp==0);
     
     switch(kp){
         case 1: kp='7'; break;
         case 2: kp='8'; break;
         case 3: kp='9'; break;
         case 4: kp='/'; break;
         
         case 5: kp='4'; break;
         case 6: kp='5'; break;
         case 7: kp='6'; break;
         case 8: kp='*'; break;
         
         case 9: kp='1'; break;
         case 10: kp='2'; break;
         case 11: kp='3'; break;
         case 12: kp='-'; break;
         
         case 13: kp='='; break;
         case 14: kp='0'; break;
         case 15: kp='='; break;
         case 16: kp='+'; break;
     }
     return kp;
}
float num1, num2, re, acum=0.0;
char aux[20]=" ", condicion = 0,te,i = 1,oper;
