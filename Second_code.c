#include <built_in.h>
# define one_rot 310
int LDR_1,LDR_2,LDR_3,LDR_4,LDR_5;
int Flag,turns,i;
int prev_pos,goal;
void LCD_show();
void Move_Delay();
// LCD module connections
sbit LCD_RS at PORTD2_bit;
sbit LCD_EN at PORTD3_bit;
sbit LCD_D4 at PORTD4_bit;
sbit LCD_D5 at PORTD5_bit;
sbit LCD_D6 at PORTD6_bit;
sbit LCD_D7 at PORTD7_bit;

sbit LCD_RS_Direction at DDD2_bit;
sbit LCD_EN_Direction at DDD3_bit;
sbit LCD_D4_Direction at DDD4_bit;
sbit LCD_D5_Direction at DDD5_bit;
sbit LCD_D6_Direction at DDD6_bit;
sbit LCD_D7_Direction at DDD7_bit;
// End LCD module connections
char txt1[] = "MOTOR ON";
char txt2[] = "NO Change";
char txt3[] = "Lcd4bit";
char txt4[] = "example";
char txt5[] = "ADC VALUE:LDR_1";
char txt6[] = "ADC VALUE:LDR_2";
char txt7[] = "ADC VALUE:LDR_3";
char txt8[] = "ADC VALUE:LDR_4";
char adc_show1[4],adc_show2[4],adc_show3[4],adc_show4[4],adc_show5[4],trns[4],gool[4],prv[4];
char current_duty;
//turns=0;

void main() {
  current_duty=125;
  Lcd_Init();                        // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  
  //LCD_show();
  DDRB = 0xFF;               // Set PORTB as output
  //DDRC = 0xFF;               // Set PORTC as output
  Lcd_Cmd(_LCD_CLEAR);
  Flag=3;
  PWM1_Init(_PWM1_FAST_MODE, _PWM1_PRESCALER_8, _PWM1_NON_INVERTED, current_duty);

  while (1) {


    LDR_1 = ADC_Read(0);    // get ADC value from 2nd channel
    LDR_2 = ADC_Read(1);
    LDR_3 = ADC_Read(2);
    LDR_4 = ADC_Read(3);
    LDR_5 = ADC_Read(4);
    prev_pos=Flag;
    if (LDR_1<LDR_2 && LDR_1<LDR_3 && LDR_1<LDR_4)
    {
    Flag=1;
    }
    else if (LDR_2<LDR_1 && LDR_2<LDR_3 && LDR_2<LDR_4)
    {
    Flag=2;
    }
    else if (LDR_3<LDR_1 && LDR_3<LDR_2 && LDR_3<LDR_4)
    {
    Flag=3;
    }
    else if (LDR_4<LDR_1 && LDR_4<LDR_2 && LDR_4<LDR_3)
    {
    Flag=4;
    }
    goal=Flag;
    Lcd_Cmd(_LCD_CLEAR);
    IntToStr(goal,adc_show1);
    IntToStr(prev_pos,adc_show2);
    IntToStr(LDR_3,adc_show3);
    IntToStr(LDR_4,adc_show4);
    IntToStr(LDR_5,adc_show5);
    Lcd_Out(1,1,adc_show1);
    Lcd_Out(1,8,adc_show2);
    //Lcd_Out(2,1,adc_show3);
    //Lcd_Out(2,6,adc_show4);
    //Delay_ms(5000);
    //Lcd_Out(2,10,adc_show5);
    //
    /*Lcd_Out(1,1,txt5);
    IntToStr(LDR_1,adc_show);
    Lcd_Out(2,1,adc_show);
    Delay_ms(5000);
    Lcd_Cmd(_LCD_CLEAR);
    Delay_ms(1000);
    //
    Lcd_Out(1,1,txt6);
    IntToStr(LDR_2,adc_show);
    Lcd_Out(2,1,adc_show);
    Delay_ms(5000);
    Lcd_Cmd(_LCD_CLEAR);
    Delay_ms(1000);
    //
    Lcd_Out(1,1,txt7);
    IntToStr(LDR_3,adc_show);
    Lcd_Out(2,1,adc_show);
    Delay_ms(5000);
    Lcd_Cmd(_LCD_CLEAR);
    Delay_ms(1000);
    //
    Lcd_Out(1,1,txt8);
    IntToStr(LDR_4,adc_show);
    Lcd_Out(2,1,adc_show);
    Delay_ms(5000);
    Lcd_Cmd(_LCD_CLEAR);
    Delay_ms(1000); */
    //Lcd_Cmd(_LCD_CLEAR);
    //Delay_ms(1000);
    //IntToStr(goal,gool);
    //IntToStr(prev_pos,prv);
    //Lcd_Out(1,1,gool);
    //Lcd_Out(1,6,prv);
    // motor rotation Start
    if (goal==prev_pos)
    {
      Lcd_Out(2,1,txt2);
      Delay_ms(1000);
    }
       else
   {

     Lcd_Out(2,1,txt1);

      if (goal>prev_pos)
      {
         for (i=prev_pos;i<=goal;i++)
         {
          PORTB.B0=0;
          PORTB.B1=1;
          Delay_ms(one_rot);
         }
      }
      else
      {
          for (i=prev_pos;i<=(4+goal);i++)
         {
          PORTB.B0=0;
          PORTB.B1=1;
          Delay_ms(one_rot);
         }
      }

   }
      PORTB.B0=1;
      PORTB.B1=1;// Motor stop
      Delay_ms(1000);
    //motor rotation End
  }

}
 void LCD_show()
 {
  Lcd_Init();                        // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off

  Lcd_Out(1,6,txt3);                 // Write text in first row
  Lcd_Out(2,6,txt4);                 // Write text in second row
  Delay_ms(2000);
  Lcd_Cmd(_LCD_CLEAR);               // Clear display

  Lcd_Out(1,1,txt1);                 // Write text in first row
  Lcd_Out(2,4,txt2);                 // Write text in second row
  Delay_ms(2000);

  // Moving text
  for(i=0; i<4; i++) {               // Move text to the right 4 times
    Lcd_Cmd(_LCD_SHIFT_RIGHT);
    Move_Delay();
  }
     for(i=0; i<7; i++) {             // Move text to the left 7 times
      Lcd_Cmd(_LCD_SHIFT_LEFT);
      Move_Delay();
    }

    for(i=0; i<7; i++) {             // Move text to the right 7 times
      Lcd_Cmd(_LCD_SHIFT_RIGHT);
      Move_Delay();
    }
 }
 void Move_Delay() {                  // Function used for text moving
  Delay_ms(500);                     // You can change the moving speed here
}