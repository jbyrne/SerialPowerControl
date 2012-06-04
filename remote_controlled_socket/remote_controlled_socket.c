//original program created by befinitiv.wordpress.com changes made by Jake Rowan Byrne May 2012

#include <avr/io.h>


#define TX_EN PD2
#define OFF PD3
#define CHANA PC5
#define CHANB PC4
#define SW1 PC3
#define SW2 PC2
#define SW3 PC1
#define SW4 PC0

#define ch1 PB1
#define ch2 PB2
#define ch3 PB3
#define ch4 PB4
#define ch5 PB5

#define TRIES 2

//all pins are pulled to 0 or left high-z

unsigned char chan;


void serial_init(void)
{

	//19200 baud
	UBRRL = 25;
	UBRRH = 0;


	UCSRA = 0;
	UCSRB |= (1 << RXEN) |(1 << TXEN);
}
/*
binary	On No.	Off No.
remote	
ABCD	

0001	1	A
0010	2	B
0100	3	C
1000	4	D
0011	5	E
0110	6	F
1100	7	G
0111	8	H
1110	9	I
1111	10	J
1010	11	K
0101	12	L
1001	13	M
1101	14	N
1011	15	O
*/


void send(unsigned char b0,unsigned char b1,unsigned char b2,unsigned char b3,unsigned char sw, unsigned char on)
{
	DDRB = 0;
	DDRC = 0;
	DDRD = 0;
	
	//DDRB = 0b00111010;--4
	DDRB = chan;

	//DDRC |=  (1 << sw);
	DDRC |=  (b0 << 0) |(b1 << 1) |(b2 << 2) |(b3 << 3);
	if(!on)
		DDRD |= (1 << OFF);

	unsigned char i;
	unsigned int delay;
	volatile int z;

	for(i=0; i < TRIES; ++i)
	{
		DDRD |= (1 << TX_EN);
		for(delay = 0; delay < 60000; ++delay)
			z++;
		DDRD &= ~(1 << TX_EN);
		for(delay = 0; delay < 60000; ++delay)
			z++;
	}

}

//This fuction writes the given "data" to
//the USART which then transmit it via TX line
void USARTWriteChar(char data)
{
   //Wait untill the transmitter is ready

   while((UCSRA & (1<<UDRE))==0)
   {
      //Do nothing
   }

   //Now write the data to USART buffer

   UDR=data;
}

int main(void)
{


	PORTD = 0;
	PORTC = 0;
	PORTB = 0;

	serial_init();


	for(;;)
	{
   		while ((UCSRA & (1 << RXC)) == 0) {  };
		
		chan = UDR;	
		
        while ((UCSRA & (1 << RXC)) == 0) {  };

		char c = UDR;
		switch(c)
		{
			case '1':
			send(0, 0, 0, 1 , SW1, 1);
			break;

			case '2':
			send(0, 0, 1, 0 , SW2, 1);
			break;

			case '3':
			send(0, 1, 0, 0 , SW3, 1);
			break;

			case '4':
			send(1, 0, 0, 0 , SW4, 1);
			break;
		
			case '5':
			send(0, 0, 1, 1 , SW1, 1);
			break;
		
			case '6':
			send(0, 1, 1, 0 , SW2, 1);
			break;
		
			case '7':
			send(1, 1, 0, 0 , SW3, 1);
			break;
		
			case '8':
			send(0, 1, 1, 1 , SW4, 1);
			break;
			
			case '9':
			send(1, 1, 1, 0 , SW1, 1);
			break;	
			
			case '10':
			send(1, 1, 1, 1 , SW1, 1);
			break;	
			
			case '11':
			send(1, 0, 1, 0 , SW1, 1);
			break;

			case '12':
			send(0, 1, 0, 1 , SW2, 1);
			break;

			case '13':
			send(1, 0, 0, 1 , SW3, 1);
			break;

			case '14':
			send(1, 1, 0, 1 , SW4, 1);
			break;
		
			case '15':
			send(1, 0, 1, 1 , SW1, 1);
			break;

			case 'A':
			send(0, 0, 0, 1 , SW1, 0);
			break;

			case 'B':
			send(0, 0, 1, 0 , SW2, 0);
			break;

			case 'C':
			send(0, 1, 0, 0 , SW3, 0);
			break;

			case 'D':
			send(1, 0, 0, 0 , SW4, 0);
			break;
		
			case 'E':
			send(0, 0, 1, 1 , SW1, 0);
			break;
		
			case 'F':
			send(0, 1, 1, 0 , SW2, 0);
			break;
		
			case 'G':
			send(1, 1, 0, 0 , SW3, 0);
			break;
		
			case 'H':
			send(0, 1, 1, 1 , SW4, 0);
			break;

			case 'I':
			send(1, 1, 1, 0 , SW3, 0);
			break;

			case 'J':
			send(1, 1, 1, 1 , SW4, 0);
			break;
		
			case 'K':
			send(1, 0, 1, 0 , SW1, 0);
			break;
		
			case 'L':
			send(0, 1, 0, 1 , SW2, 0);
			break;
		
			case 'M':
			send(1, 0, 0, 1 , SW3, 0);
			break;
		
			case 'N':
			send(1, 1, 0, 1 , SW4, 0);
			break;
		
			case 'O':
			send(1, 0, 1, 1 , SW4, 0);
			break;
				
			default:
			
			break;
		}		
	} 
}
