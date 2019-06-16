#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


int c=0,t=0;
uint16_t count = 0;                     // Gan so dem
int dich = 0;
char str[10];

void led_nhay(int so)
{
	char sang_dan[]={0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};
	for(int i=0; i<=so; i++)
	{
		PORTC = sang_dan[i];
		_delay_ms(5);
	}
}

int main(void)
{
	
	//lcd
	
	//lcd_init(LCD_DISP_ON);
	
	
	// enable regigter B-D
	DDRB &=~(1<<PD1);
	DDRC =0xff;
	DDRD =0xff;
	DDRA |=(1<<PA0);
	
	// khoi tao timer1
	
	TCCR1A=0;
	TCCR1B=0x07;
	TCNT1=0;
	
	// khoi tao timer0
	
	TCCR0=(1<<CS00)|(1<<CS01);
	TCNT0=6;
	TIMSK=(1<<TOIE0);
	
	// interrupt INT2

	GICR |= (1<< INT2);
	MCUCSR |= (1<<ISC2);
	while((TIFR&0x01)==0);          // cowf bao len 1
	TIFR = 0;
	sei();

	while (1)
	{
		led_nhay(dich);
	}
}

ISR(TIMER0_OVF_vect) // 1us                      // hien thi led xung vao
{
	t++;
	TCNT0=6;
	if(t==999)        // doc so dem sau 1s
	{
		count = TCNT1;
		dich = int(count/13);
		if (dich>8) dich =8;
		TCNT1 = 0;
		t=0;
	}
}

ISR(INT2_vect)
{
		PORTA |=(1<<PA0);
		_delay_ms(4);
		PORTA &=~(1<<PA0);
		_delay_ms(4);

}


