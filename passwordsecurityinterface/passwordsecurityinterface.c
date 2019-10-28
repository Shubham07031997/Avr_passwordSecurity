#include<avr/io.h>
#define F_CPU 8000000
#include<util/delay.h>
#include<lcdavr.h>
int x;
unsigned char a[5];
unsigned char pas[5]={"12345"};
unsigned int f,m=1,p;
unsigned char keyscan();
int main()
{	
    unsigned int i;
	DDRA = 0X00;
	DDRD = 0X0FF;
	DDRC=0XFF;
	PORTA= 0XFF;
	DDRB = 0XFF;
	lcd_init();
	
/*	lcd_command(0x80);
	lcd_string("enter password");
	lcd_command(0xc0);*/
	
  

	while(1)
	{   
	  lcd_command(0x80);
	    lcd_string("ENTER YOUR");
		lcd_command(0xc0);
		lcd_string("PASSWORD");
		_delay_ms(50);
		lcd_clear();
		for(i=0;i<5;i++)
		{
	             
			  a[i]=keyscan();
			  if(i==0)
			  {
			  lcd_command(0x01);
			  lcd_data(' ');
			  }
			  lcd_data('*');
			 }
         
		 if(a[0]==pas[0]&& a[1]==pas[1]&& a[2]==pas[2]&& a[3]==pas[3]&& a[4]==pas[4])
		  {
		    m=1;
			}
			else
			{
			  m=0;
			  }
			  if(m==1)
			  {
			     lcd_clear();
				 lcd_command(0x80);
				 lcd_string("PASSWORD MATCHED");
				 lcd_command(0xc0);
				 lcd_string("access granted");
				 _delay_ms(50);
				 lcd_clear();
				 lcd_data(keyscan());
				 _delay_ms(100);

				 x=keyscan();
				 lcd_data(x);
				 if(x=='2')
				 { lcd_command(0x80);
				 lcd_string("motor forward");
				   PORTC=0b10100000;
				   _delay_ms(100);
				   PORTC=0x00;
				   lcd_clear();
				   }
                     if(x=='4')
				 { lcd_command(0x80);
				 lcd_string("motor right");
				   PORTC=0b00100000;
				   _delay_ms(100);
				   PORTC=0x00;
				   lcd_clear();
				   }
				   if(x=='6')
				 { lcd_command(0x80);
				 lcd_string("motor left");
				   PORTC=0b10000000;
				   _delay_ms(100);
				   PORTC=0x00;
				   lcd_clear();
				   }
				   if(x=='8')
				 { lcd_command(0x80);
				 lcd_string("motor backward");
				   PORTC=0b01010000;
				   _delay_ms(100);
				   PORTC=0x00;
				   lcd_clear();
				   }
                        
				 p=0;
				 _delay_ms(100);
				 }  
				 else if(m==0)
				 {
				   p++;
				   lcd_clear();
				   lcd_command(0x80);
				   lcd_string("wrong pasword");
				   lcd_command(0xc0);
				   lcd_string("access denied");
				   _delay_ms(100);
				   lcd_clear();
				   m=1;
				   if(p==3)
				   {
				      lcd_clear();
					  lcd_command(0x80);
					  lcd_string("error");
					  lcd_clear();
					  }
					  }
					
                         
					  
				 
	}
	
	return 0;
}
//*****************************************SUBROTINE************************************************



unsigned char keyscan()
{
		while(1)
	{      
	PORTD = 0X0e;// column no.1 is taken as output
	_delay_ms(10);  /////must for response at porta when key press
	if((PINA&0b00000001)==0){ return '7';}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010));
	   return'4';}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return '1';}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return '@';}

	PORTD = 0X0d;//column no. two is taken as output
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001));
	return '8';}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return '5';}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100));
	  return '2';}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return '0';}

	PORTD = 0X0b;//column no. three is taken as output
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return '9';}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010));
	  return '6';}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return '3';}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return '=';}											

	PORTD = 0X07;//column no.four is taken as output
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return '/';}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return 'x';}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return '-';}
    if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return '+';}

	}	  
 }
//************************************END**************************************************

