// Use INT0 to record channel A
// Use INT1 to record channel B

// Global Variables     
int X,Y,temp,d5;
//const unsigned char MSG1[21] = "RB0 to roll      "; 

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "LCD_portD.c"

// High-priority service
void interrupt IntServe(void)
{   
   if (INT1IF) {
      X += 1;
      INT1IF = 0;
      }   
   if (INT2IF) {
      Y += 1;
      INT2IF = 0;
      }   

   }
   

         
// Main Routine

void main(void)
{
   unsigned char i;
   unsigned int j;
   double sec, inch;

   TRISA = 0;
   TRISB = 0xFF;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD
   //LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);

// Initialize Serial Port to 9600 baud
   TRISC = TRISC | 0xC0;
   TXIE = 0;
   RCIE = 0;
   BRGH = 0;
   BRG16 = 1;
   SYNC = 0;
   SPBRG = 255;
   TXSTA = 0x22;
   RCSTA = 0x90;


// Turn on INT1 interrupt
   INT1IE = 1;
   TRISB1 = 1;
   INTEDG1 = 1;

// Turn on INT2 interrupt
   INT2IE = 1;
   TRISB2 = 1;
   INTEDG2 = 1;

// turn on all interrupts
   GIE = 1;

   temp = 0;
   X = 0;
   Y = 0;

   while(1) {
		while(!RB0);
 		while(RB0) {
 			d5 = (d5 + 1) % 5;
		 }
 		d5 = d5 + 1;
	    LCD_Move(0,0); LCD_Out(d5,1,0);
		while(!RB1 && !RB2);
      	LCD_Move(1,0);  
      	LCD_Out(X, 3, 0);
      	LCD_Out(Y, 3, 0);
      	Wait_ms(20);

		 while(!TRMT); TXREG = X + 48; // collect data on the serial port
 		 while(!TRMT); TXREG = 13; // carriage return
		 while(!TRMT); TXREG = 10; // line feed      
	}

   }

