//Ziad Ayoub CU1900705
//Assignment 2 Code - PicSimLab


//Declerations of LCD pins to initilize them 
sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D0 at RD0_bit;
sbit LCD_D1 at RD1_bit;
sbit LCD_D2 at RD2_bit;
sbit LCD_D3 at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D0_Direction at TRISD0_bit;
sbit LCD_D1_Direction at TRISD1_bit;
sbit LCD_D2_Direction at TRISD2_bit;
sbit LCD_D3_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;


//Declerations of variables for temprature readings and temprature limits 
unsigned char TempLimUpper = 60;
char TempLimUpperStr[3];	//Creats varibale with length of 3 characters

unsigned char TempLimLower = 20;
char TempLimLowerStr[3];	//Creats varibale with length of 3 characters

unsigned char Temp;			//Creats the variable Temp as int
char TempStr[3];			//Creats varibale with length of 3 characters




//This funcation returns the the value of the temprature upper limit as well as outputting it on the LCD.
//It also moniters specific button presses, which when pressed either incrment or decremnet the value of the limit.
int UpperLimit()
{
 //If the button RB4 is pressed, the the Temp Upper Limit increases by 1
 if (RB4_bit == 1)
 {TempLimUpper = TempLimUpper+1;}

 //If the button RB3 is pressed, the the Temp Upper Limit decreases by 1
 if (RB3_bit == 1)
 {TempLimUpper = TempLimUpper-1;}


  //Converts the temp upper limit into a string then writes it on to the LCD
  //"LHi" stands for "Limit "Limit Higher"
  ShortToStr(TempLimUpper, TempLimUpperStr); 
  Lcd_Out(2,13,TempLimUpperStr);
  Lcd_Out(2,10,"LHi:");
  
  //Returns temprature upper limit
  return TempLimUpper;
}




//This funcation returns the the value of the temprature lower limit as well as outputting it on the LCD.
//It also moniters specific button presses, which when pressed either incrment or decremnet the value of the limit.
int LowerLimit()
{

 //If the button RB1 is pressed, the the Temp Lower Limit increases by 1
  if (RB1_bit == 1)
  {TempLimLower = TempLimLower+1;}

 //If the button RB2 is pressed, the the Temp Lower Limit decreases by 1
  if (RB2_bit == 1)
  {TempLimLower = TempLimLower-1;}
  
  
  //Converts the temp lower limit into a string then writes it on to the LCD
  //"LLo" stands for "Limit "Limit Lower"
  ShortToStr(TempLimLower, TempLimLowerStr);
  Lcd_Out(2,4,TempLimLowerStr);
  Lcd_Out(2,1,"LLo:");
  
  //Returns temprature lower limit
  return TempLimLower;
}




void main()
{
  //For LCD intialzation
  ANSELD=0;		//Sets port D as digital
  TRISD=0;		//Sets port D as output
  PORTD=0;		

  ANSELE=0;		//Sets port E as digital
  TRISE=0;		//Sets for E as output	
  PORTE=0;		
  
  Lcd_Init();                // Initialize LCD  
  
  
  //For push buttons
  ANSELB=0;		//Stes port B as digital
  TRISB=0xff;	//Sets port B as Input

  //For ADC intialzation
  ANSELA=0xff;		//Sets port A as analoug
  TRISA=0xff;		//Sets port A as Input
  ADC_Init();		//Initializes the analoug to digital converter

  // For Heater and Buzzer
  ANSELC=0;			//Sets port C to analoug
  TRISC=0;			//Sets port C to output


  Lcd_Cmd(_LCD_CLEAR);       // Clear LCD display
  Lcd_Cmd(_LCD_CURSOR_OFF);  // Turns cursor off


  Lcd_Out(1,1,"Temp Val:");     // Prepare and output static text on LCD
  Lcd_Out(2,1,"LHi:");      	// Prepare and output static text on LCD
  Lcd_Out(2,10,"LLo:");     	// Prepare and output static text on LCD
  
  
  RC2_bit=1;   //Cooler turned on, can be altered on the simualtion on or off
  RC5_bit=1;   //Heater turned on, can be altered on the simualtion on or off
  
  
  while(1)
  {
   //Reads the value from the LM35 sensor and converts it into degrees celcuis.
   //Outputs the temp reading onto the LCD
   Lcd_Out(1,1,"Temp Val:");
   Temp = ADC_Read(2)*0.489;
   WordToStr(Temp, TempStr);
   Lcd_Out(1,10,TempStr);
   
   //Gets the temp upper and lower limit for their respective funcation.
   //The funcations return the limit values as well as output the limit values on the LCD
   TempLimLower = LowerLimit();
   TempLimUpper = UpperLimit();
   
 
   //If the temp excued the limtits, it turns on the buzzer on which is conected to RC1.
   if (((char)Temp >= TempLimUpper) || ((char)Temp <= TempLimLower))
   {RC1_bit=1;}
   else {RC1_bit=0;}
  }
}
