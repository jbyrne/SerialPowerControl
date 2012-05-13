

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




void serial_init(void)
{

	//19200 baud
	UBRRL = 25;
	UBRRH = 0;


	UCSRA = 0;
	UCSRB |= (1 << RXEN) |(1 << TXEN);
}






void send(unsigned char sw, unsigned char channel, unsigned char on)
{
	DDRB = 0;
	DDRC = 0;
	DDRD = 0;

	DDRB = 0b00111010;
	//DDRB |= (1 << ch1) | (0 << ch2) | (0 << ch3) | (1 << ch4) | (1 << ch5);


	DDRC |= (1 << channel) | (1 << sw);

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
		if(UCSRA & (1 << RXC))
		{
			char c = UDR;
      while (!(UCSRA & (1 << UDRE))) {}; // Do nothing until UDR is ready for more data to be written to it

      UDR = c; // Echo back the received byte back to the computer
       USARTWriteChar(c);

			switch(c)
			{
				case '1':
				send(SW1, CHANA, 1);
				break;

				case '2':
				send(SW2, CHANA, 1);
				break;

				case '3':
				send(SW3, CHANA, 1);
				break;

				case '4':
				send(SW4, CHANA, 1);
				break;
			
				case '5':
				send(SW1, CHANB, 1);
				break;
			
				case '6':
				send(SW2, CHANB, 1);
				break;
			
				case '7':
				send(SW3, CHANB, 1);
				break;
			
				case '8':
				send(SW4, CHANB, 1);
				break;

				case 'A':
				send(SW1, CHANA, 0);
				break;

				case 'B':
				send(SW2, CHANA, 0);
				break;

				case 'C':
				send(SW3, CHANA, 0);
				break;

				case 'D':
				send(SW4, CHANA, 0);
				break;
			
				case 'E':
				send(SW1, CHANB, 0);
				break;
			
				case 'F':
				send(SW2, CHANB, 0);
				break;
			
				case 'G':
				send(SW3, CHANB, 0);
				break;
			
				case 'H':
				send(SW4, CHANB, 0);
				break;
			

			
				default:
				
				break;
			}
		}			
	} 











//	DDRD |= (1 << TX_EN);


//	DDRC = (1 << CHANA) | (1 << SW2);



}
