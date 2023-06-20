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

#define dir_keypad (TRISB)

// Conexões do Módulo LCD
sbit LCD_RS at RE0_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISE0_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// Fim das conexões do 7587dulo LCD//

/* ** Declaração de Variáveis ** */
unsigned char tecla = 'n';
unsigned char operacao = 'n';
unsigned char txt[16], rst[7];

unsigned int ValorA, ValorB, Resultado, Resto, i, num;
unsigned int reset = 0, ativo = 1;
unsigned int Nums1[10], Nums2[10];
unsigned int qntdA, qntdB;


/* ** Protótipos de Função ** */
char varrer();
void Key_Init();
char espera_tecla();

/* ** Função Principal ** */
void main(){
     Key_Init();
     Lcd_Init();
     INTCON2.RBPU = 1;
     ValorA,ValorB,Resultado = 0,0,0;
     operacao = 'n';
     i = 0;
     num = 1;
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     //Lcd_Out(1,1,"Tecla Acionada");
     Lcd_Cmd(_LCD_FIRST_ROW);
     while(1){
        tecla = espera_tecla();
        if(reset == 1){Lcd_Cmd(_LCD_CLEAR); reset = 0;}
        if(tecla == ' '){switch (ativo){case 1: Lcd_Cmd(_LCD_TURN_OFF); ativo = 0; break;  case 0: Lcd_Cmd(_LCD_TURN_ON); ativo = 1; break;}}
        if(tecla != ' '){Lcd_Chr_Cp(tecla);

        if(tecla == '+' || tecla == '-' || tecla == '*' || tecla == '/') {operacao = tecla; i=0; num = 2;}
        /*if(operacao == 'n'){
        //Valor_A = tecla - '0';
        Nums1[i] = tecla - '0';
        i++;7
        } */
        if(num == 1 && tecla != operacao && tecla != '='){
         Nums1[i] = tecla - '0';
         qntdA = i+1; i++;
        }
        if(num == 2 && tecla != operacao && tecla != '='){
         Nums2[i] = tecla - '0';
         qntdB = i+1; i++;
        }
        /*if(operacao == '+' || operacao == '-' || operacao == '' || operacao == '/'){if(tecla != '='){
        ValorB = tecla - '0';

        }}*/

        if(tecla == '='){
         switch (qntdA){
          case 1: ValorA = Nums1[0]; break;
          case 2: ValorA = Nums1[0] * 10 + Nums1[1]; break;
          case 3: ValorA = Nums1[0] * 100 + Nums1[1] * 10 + Nums1[2]; break;
          case 4: ValorA = Nums1[0] * 1000 + Nums1[1] * 100 + Nums1[2] * 10 + Nums1[3]; break;
          case 5: ValorA = Nums1[0] * 10000 + Nums1[1] * 1000 + Nums1[2] * 100 + Nums1[3] * 10 + Nums1[4]; break;
          case 6: ValorA = Nums1[0] * 100000 + Nums1[1] * 10000 + Nums1[2] * 1000 + Nums1[3] * 100 + Nums1[4] * 10 + Nums1[5]; break;
          case 7: ValorA = Nums1[0] * 1000000 + Nums1[1] * 100000 + Nums1[2] * 10000 + Nums1[3] * 1000 + Nums1[4] * 100 + Nums1[5] * 10 + Nums1[6]; break;
           default: ValorA = 0;
        }
         switch (qntdB){
          case 1: ValorB = Nums2[0]; break;
          case 2: ValorB = Nums2[0] * 10 + Nums2[1]; break;
          case 3: ValorB = Nums2[0] * 100 + Nums2[1] * 10 + Nums2[2]; break;
          case 4: ValorB = Nums2[0] * 1000 + Nums2[1] * 100 + Nums2[2] * 10 + Nums2[3]; break;
          case 5: ValorB = Nums2[0] * 10000 + Nums2[1] * 1000 + Nums2[2] * 100 + Nums2[3] * 10 + Nums2[4]; break;
          case 6: ValorB = Nums2[0] * 100000 + Nums2[1] * 10000 + Nums2[2] * 1000 + Nums2[3] * 100 + Nums2[4] * 10 + Nums2[5]; break;
          case 7: ValorB = Nums2[0] * 1000000 + Nums2[1] * 100000 + Nums2[2] * 10000 + Nums2[3] * 1000 + Nums2[4] * 100 + Nums2[5] * 10 + Nums2[6]; break;
           default: ValorB = 0;
        }


         switch (operacao){
          case '+': Resultado = ValorA + ValorB; break;
          case '-': Resultado = ValorA - ValorB; break;
          case '*': Resultado = ValorA * ValorB; break;
          case '/': Resultado = ValorA / ValorB; Resto = ValorA % ValorB; break;
           default: Resultado = ValorA;

        }
         IntToStr(Resultado, txt);  IntToStr(Resto, rst);
         LTrim(txt); LTrim(rst);

         Lcd_Out(2,1,txt);  if(Resto != 0){ Lcd_Out(2,9,rst);}
         Lcd_Cmd(_LCD_RETURN_HOME);
         reset = 1;
         Resto = 0;
         operacao = 'n';
         i = 0;
         num = 1;
         qntdA, qntdB = 0,0;

     }
     }
}
}

/* ** Script de Funções ** */

char varrer(){

    Col_1 = 0; Col_2 = 1; Col_3 = 1; Col_4 = 1; Delay_ms(50);
    if(La == 0) {Delay_ms(50); while(La == 0); return '7';}
    if(Lb == 0) {Delay_ms(50); while(Lb == 0); return '4';}
    if(Lc == 0) {Delay_ms(50); while(Lc == 0); return '1';}
    if(Ld == 0) {Delay_ms(50); while(Ld == 0); return ' ';}
    Col_1 = 1; Col_2 = 0; Col_3 = 1; Col_4 = 1; Delay_ms(50);
    if(La == 0) {Delay_ms(50); while(La == 0); return '8';}
    if(Lb == 0) {Delay_ms(50); while(Lb == 0); return '5';}
    if(Lc == 0) {Delay_ms(50); while(Lc == 0); return '2';}
    if(Ld == 0) {Delay_ms(50); while(Ld == 0); return '0';}
    Col_1 = 1; Col_2 = 1; Col_3 = 0; Col_4 = 1; Delay_ms(50);
    if(La == 0) {Delay_ms(50); while(La == 0); return '9';}
    if(Lb == 0) {Delay_ms(50); while(Lb == 0); return '6';}
    if(Lc == 0) {Delay_ms(50); while(Lc == 0); return '3';}
    if(Ld == 0) {Delay_ms(50); while(Ld == 0); return '=';}
    Col_1 = 1; Col_2 = 1; Col_3 = 1; Col_4 = 0; Delay_ms(50);
    if(La == 0) {Delay_ms(50); while(La == 0); return '/';}
    if(Lb == 0) {Delay_ms(50); while(Lb == 0); return '*';}
    if(Lc == 0) {Delay_ms(50); while(Lc == 0); return '-';}
    if(Ld == 0) {Delay_ms(50); while(Ld == 0); return '+';}

    return 'n';
}

char espera_tecla(){

    char key = 'n';
    while (key == 'n') {key = varrer();}
    return key;
}

void Key_Init(){

    PORTB = 0x00;
    ADCON1 = 0x0F;
    dir_keypad = 0x0F;


}
