
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define LED PORTC
#define BTN PORTD 
	
int count =	0;
ISR(TIMER1_OVF_vect)
{
	TCCR1B = 0b00000000;
	count++;
	TCCR1B = 0b00000011;
	TCNT1=49536;
}

int main(void)
{
	TCCR1B = 0b00000011;
	DDRD = 0b0000000;
	DDRC = 0b0000111;
	BTN = 0b11111111; 
	TIMSK = 0b00000100;
	SREG = 0b10000000;
  do
  {	  
	TCNT1=49536;
	if(PIND == 0b11111011 )
	{		
		while(count <50)
		{
			GlowFirstLight();			
		}
		while(count <55)	 
		{
			GlowSecondLight();
		}
		while(count <60)
		{
			int num = count;
			count = 0;
			TraficBroke(count);
			count = num+2;
		}
		while(count <100)
		{
			GlowThirtLight();
		}
		OffLights();
		count = 0;
	}
	else if(PIND == 0b11110111)
	{
		while(count<1)
		{
			GlowAllLight();
		}
		while(count <2)
		{
			OffLights();
		}
		count = 0;
	}
	else if(PIND == 0b11101111)
	{
		TraficBroke(count);
	}
	else
	{
		OffLights();
		count = 0;
	}  	  
  }while(1);
}
void GlowFirstLight(void)
{
	LED = 0b0000001;		
}
void GlowSecondLight(void)
{
	LED = 0b0000010;
}
void GlowThirtLight(void)
{
	LED = 0b0000100;
}
void GlowAllLight(void)
{
	LED = 0b0000111;
}
void OffLights(void)
{
	LED = 0;
}
void TraficBroke(void)
{
	while(count<1)
	{
		GlowSecondLight();
	}
	while(count <2)
	{
		OffLights();
	}
	count = 0;
}



