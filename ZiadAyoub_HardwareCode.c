//Ziad Ayoub CU1900705
//Assignment 2 Code - Hardwear Implimentation


//Declerations of LCD pins to initilize them 
sbit LCD_RS at LATA3_bit;
sbit LCD_EN at LATB1_bit;
sbit LCD_D4 at LATB2_bit;
sbit LCD_D5 at LATB3_bit;
sbit LCD_D6 at LATB4_bit;
sbit LCD_D7 at LATB5_bit;

sbit LCD_RS_Direction at TRISA3_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;


//Declerations of variables for temprature readings and temprature limits 
int Temp;			//Creats the variable Temp as int
char TempStr[3];	//Creats varibale with length of 3 characters

int TempLimUpper = 60;		//Creats the variable for the temp upper limit as an integer and sets it to 60 degrees C
int TempLimLower = 20;		//Creats the variable for the temp lower limit as an integer and sets it to 20 degrees C

char TempLimUpperStr[3];	//Creats varibale with length of 3 characters
char TempLimLowerStr[3];	//Creats varibale with length of 3 characters


char keypadPort at PORTD;	//Specifes the location of the keypad at port D


Keypad_Init();		//Initializes the Keypad
int kp;   //Creats the varible kp (Key Pressed) as inteager



//This funcation returns the the value of the temprature lower limit as well as outputting it on the LCD.
//It also moniters specific button presses, which when pressed allows for the limit to be increased or decreased by a certain value.
//This value is determined by pressing a second button on the keypad.
int LowerLim(){

  //Pressed C button on keypad - Increase Lower Limit
  if (Keypad_Key_Click() == 12) 
  {
    kp = 0;		//Sets key pressed to nothing
	//Keeps in the while loop until a keypad a number from 0-9 is pressed on the keypad.
    while(kp==0)
    {
      kp = Keypad_Key_Click();		//Sets the key pressed on the keypad
	  //If the keys pressed are "A","B","C","D","#",or"*" the input is invalid so sets the key pressed back to nothing (kp=0)
      if((kp==4) || (kp==8) || (kp==12) || (kp==16) || (kp==13) || (kp==15))
      {kp=0;}
    }
	//Switch case for each of the possible numbers entered through the keypad.
	//Adds the respective number pressed to the Temp lower limit.
    switch (kp) {
       case 1: TempLimLower = TempLimLower+1; break;
       case 2: TempLimLower = TempLimLower+2; break;
       case 3: TempLimLower = TempLimLower+3; break;
       case 5: TempLimLower = TempLimLower+4; break;
       case 6: TempLimLower = TempLimLower+5; break;
       case 7: TempLimLower = TempLimLower+6; break;
       case 9: TempLimLower = TempLimLower+7; break;
       case 10: TempLimLower = TempLimLower+8; break;
       case 11: TempLimLower = TempLimLower+9; break;
       case 14: TempLimLower = TempLimLower+0; break;
    }
  }

  //Pressed D button on keypad - Decrease Lower Limit
  else if (Keypad_Key_Click() == 16) 
  {
    kp = 0;		//Sets key pressed to nothing
	//Keeps in the while loop until a keypad a number from 0-9 is pressed on the keypad.
    while(kp==0)
    {
      kp = Keypad_Key_Click();		//Sets the key pressed on the keypad
	  //If the keys pressed are "A","B","C","D","#",or"*" the input is invalid so sets the key pressed back to nothing (kp=0)
      if((kp==4) || (kp==8) || (kp==12) || (kp==16) || (kp==13) || (kp==15))
      {kp=0;}
    }
	//Switch case for each of the possible numbers entered through the keypad.
	//Subtracts the respective number pressed to the Temp lower limit.
	//If the number chosen is larger than the value of the lower limit, it does not subtract it and keeps the limit as is.
    switch (kp) {
       case 1: if(TempLimLower>=1){TempLimLower = TempLimLower-1;} break;
       case 2: if(TempLimLower>=2){TempLimLower = TempLimLower-2;} break;
       case 3: if(TempLimLower>=3){TempLimLower = TempLimLower-3;} break;
       case 5: if(TempLimLower>=4){TempLimLower = TempLimLower-4;} break;
       case 6: if(TempLimLower>=5){TempLimLower = TempLimLower-5;} break;
       case 7: if(TempLimLower>=6){TempLimLower = TempLimLower-6;} break;
       case 9: if(TempLimLower>=7){TempLimLower = TempLimLower-7;} break;
       case 10: if(TempLimLower>=8){TempLimLower = TempLimLower-8;} break;
       case 11: if(TempLimLower>=9){TempLimLower = TempLimLower-9;} break;
       case 14: TempLimLower = TempLimLower-0; break;
    }
  }
  
  //Converts the temp lower limit into a string then writes it on to the LCD
  //"LLo" stands for "Limit "Limit Lower"
  ShortToStr(TempLimLower, TempLimLowerStr);
  Lcd_Out(2,4,TempLimLowerStr);
  Lcd_Out(2,1,"LLo:");
  
  //Returns temprature lower limit
  return TempLimLower;
}




//This funcation returns the the value of the temprature upper limit as well as outputting it on the LCD.
//It also moniters specific button presses, which when pressed allows for the limit to be increased or decreased by a certain value.
//This value is determined by pressing a second button on the keypad.
int UpperLim(){

  //Pressed A button on keypad - Increase Upper Limit
  if (Keypad_Key_Click() == 4) 
  {
    kp = 0;		//Sets key pressed to nothing
	//Keeps in the while loop until a keypad a number from 0-9 is pressed on the keypad.
    while(kp==0)
    {
      kp = Keypad_Key_Click();		//Sets the key pressed on the keypad
	  //If the keys pressed are "A","B","C","D","#",or"*" the input is invalid so sets the key pressed back to nothing (kp=0)
      if((kp==4) || (kp==8) || (kp==12) || (kp==16) || (kp==13) || (kp==15))
      {kp=0;}
    }
	//Switch case for each of the possible numbers entered through the keypad.
	//Adds the respective number pressed to the Temp upper limit.
    switch (kp) {
       case 1: TempLimUpper = TempLimUpper+1; break;
       case 2: TempLimUpper = TempLimUpper+2; break;
       case 3: TempLimUpper = TempLimUpper+3; break;
       case 5: TempLimUpper = TempLimUpper+4; break;
       case 6: TempLimUpper = TempLimUpper+5; break;
       case 7: TempLimUpper = TempLimUpper+6; break;
       case 9: TempLimUpper = TempLimUpper+7; break;
       case 10: TempLimUpper = TempLimUpper+8; break;
       case 11: TempLimUpper = TempLimUpper+9; break;
       case 14: TempLimUpper = TempLimUpper+0; break;
    }
  }

  //Pressed B button on keypad - Increase Upper Limit
  else if (Keypad_Key_Click() == 8) 
  {
    kp = 0;		//Sets key pressed to nothing
	//Keeps in the while loop until a keypad a number from 0-9 is pressed on the keypad.
    while(kp==0)
    {
      kp = Keypad_Key_Click();		//Sets the key pressed on the keypad
	  //If the keys pressed are "A","B","C","D","#",or"*" the input is invalid so sets the key pressed back to nothing (kp=0)
      if((kp==4) || (kp==8) || (kp==12) || (kp==16) || (kp==13) || (kp==15))
      {kp=0;}
    }
	//Switch case for each of the possible numbers entered through the keypad.
	//Subtracts the respective number pressed to the Temp upper limit.
	//If the number chosen is larger than the value of the lower limit, it does not subtract it and keeps the limit as is.
    switch (kp) {
       case 1: if(TempLimUpper>=1){TempLimUpper = TempLimUpper-1;} break;
       case 2: if(TempLimUpper>=2){TempLimUpper = TempLimUpper-2;} break;
       case 3: if(TempLimUpper>=3){TempLimUpper = TempLimUpper-3;} break;
       case 5: if(TempLimUpper>=4){TempLimUpper = TempLimUpper-4;} break;
       case 6: if(TempLimUpper>=5){TempLimUpper = TempLimUpper-5;} break;
       case 7: if(TempLimUpper>=6){TempLimUpper = TempLimUpper-6;} break;
       case 9: if(TempLimUpper>=7){TempLimUpper = TempLimUpper-7;} break;
       case 10: if(TempLimUpper>=8){TempLimUpper = TempLimUpper-8;} break;
       case 11: if(TempLimUpper>=9){TempLimUpper = TempLimUpper-9;} break;
       case 14: TempLimUpper = TempLimUpper-0; break;
    }
  }

  //Converts the temp upper limit into a string then writes it on to the LCD
  //"LHi" stands for "Limit "Limit Higher"
  ShortToStr(TempLimUpper, TempLimUpperStr); 
  Lcd_Out(2,13,TempLimUpperStr);
  Lcd_Out(2,10,"LHi:");

  //Returns temprature upper limit
  return TempLimUpper;
}




void main() {
  ANSELA = 0x00000010;		//Sets port A as digital expect for pin 1 as analoug which is where the LM35 is connected
  TRISA = 0x00000010;		//Sets port A as output expect for pin 1 as input which is where the LM35 is connected
  
  ANSELB = 0;		//Sets port B as digital
  ANSELC = 0;		//Sets port C as digital
  ANSELD = 0;		//Sets port D as digital
  
  ANSELE = 0xff;	//Sets port E as analoug
  TRISE = 0;		//Sets for E as output	

  ADC_Init();		//Initializes the analoug to digital converter

  Lcd_Init();			//Initializes the analoug to digital converter
  Lcd_Cmd(_LCD_CLEAR);				//Clear LCD display
  Lcd_Cmd(_LCD_CURSOR_OFF);			//Turns cursor off
  Lcd_Out(1, 1, "Temp Val: ");		//Prepare and output static text on LCD


  while(1){
    //Reads the value from the LM35 sensor and converts it into degrees celcuis.
    //Outputs the temp reading onto the LCD
    Temp = ADC_Read(1) * 0.489;
    WordToStr(Temp, TempStr);
    Lcd_Out(1,11,TempStr);


   //Gets the temp upper and lower limit for their respective funcation.
   //The funcations return the limit values as well as output the limit values on the LCD
    TempLimLower = LowerLim();
    TempLimUpper = UpperLim();    
    
	
   //If the temp excued the limtits, it turns on the buzzer on which is conected to port E.    
    if ((Temp >= TempLimUpper) || (Temp <= TempLimLower))
    {PORTE=0xff;}
    else
    {PORTE=0;}
    
  }
}