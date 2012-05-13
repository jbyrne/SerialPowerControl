

#include <avr/io.h>
#include<util/delay.h>
#define LEDON PORTC |= (0x00)

#define LEDOFF PORTC &= ~(0x00)

#define LEDTOGGLE PORTC ^=(0x00)


#define TX_EN PD2
#define OFF PD3
#define CHANA PC5
#define CHANB PC4
#define SW1 PC3
#define SW2 PC2
#define SW3 PC1
#define SW4 PC0


#define TRIES 1

//all pins are pulled to 0 or left high-z




void serial_init(void)
{

	//19200 baud
	UBRRL = 25;
	UBRRH = 0;


	UCSRA = 0;
	UCSRB = (1 << RXEN);
}






void send(unsigned char sw, unsigned char channel, unsigned char on)
{


}


int main(void)
{

DDRC  = 0xff;

	//PORTC = 0;
serial_init();


   while(!(UCSRA & (1<<RXC)))
   {
      //Do nothing
PORTC =  0xff;
   }
			char c = UDR;

			switch(c)
			{
				case '1':
				PORTC = 0x00;
				_delay_ms(100);
				break;

				case '2':
				PORTC = 0x00;
				_delay_ms(100);
				PORTC = 0xff;
				_delay_ms(100);
				PORTC = 0x00;
				_delay_ms(1000);
				break;

				
				default:
				break;
			}
					
	











//	DDRD |= (1 << TX_EN);


//	DDRC = (1 << CHANA) | (1 << SW2);



}



#include <avr/io.h>
#include <inttypes.h>
#include<util/delay.h>

#define TX_EN PD2
#define OFF PD3
#define CHANA PC5
#define CHANB PC4
#define SW1 PC3
#define SW2 PC2
#define SW3 PC1
#define SW4 PC0


#define TRIES 1

//all pins are pulled to 0 or left high-z




void serial_init(uint16_t ubrr_value)
{

	//19200 baud
	//UBRRL = 25;
	//UBRRH = 0;
  	 UBRRL = ubrr_value;
  	 UBRRH = (ubrr_value>>8);

 	 UCSRC=(1<<URSEL)|(3<<UCSZ0);
	UCSRA = 0;
	UCSRB=(1<<RXEN)|(1<<TXEN);
}






void send(unsigned char sw, unsigned char channel, unsigned char on)
{
	DDRC = 0;
	DDRD = 0;


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



int main(void)
{


	PORTD = 0;
	PORTC = 0;

	serial_init(51);


	for(;;)
	{

		if(UCSRA & (1 << RXC))
		{
			char c = UDR;
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
				send(SW2, CHANA, 1);
				//PORTC = 0xff;
				//_delay_ms(300);
				break;
			}
		}			
	}











//	DDRD |= (1 << TX_EN);


//	DDRC = (1 << CHANA) | (1 << SW2);



}




//////////////////////////////////////////





#include <avr/io.h>
#include <avr/interrupt.h>

#define TX_EN PD2
#define OFF PD3
#define CHANA PC5
#define CHANB PC4
#define SW1 PC3
#define SW2 PC2
#define SW3 PC1
#define SW4 PC0

#define TRIES 3

//all pins are pulled to 0 or left high-z



//
void serial_init()
{


   //Set Baud rate

   UBRRL = 25;
   UBRRH = 0;
// UBRRL = ubrr_value;
  // UBRRH = (ubrr_value>>8);
   //UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
 //UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register


   /*Set Frame Format


   >> Asynchronous mode
   >> No Parity
   >> 1 StopBit

   >> char size 8

   */
//UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes
//UCSRC=0;
//   UCSRC|=(1<<URSEL)|(3<<UCSZ0);
UCSRA = 0;
   //Enable The receiver and transmitter
//UCSRB =0;
   //UCSRB=(1<<RXEN)|(1<<TXEN);
 UCSRB |= (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
// Enable the USART Recieve Complete interrupt (USART_RXC)


}

//This fuction writes the given "data" to
//the USART which then transmit it via TX line
void USARTWriteChar(char data)
{
   //Wait untill the transmitter is ready

   while(!(UCSRA & (1<<UDRE)))
   {
      //Do nothing
   }

   //Now write the data to USART buffer

   UDR='a';
   UDR='a';
}

//This function is used to read the available data
//from USART. This function will wait untill data is
//available.
char USARTReadChar()
{
   //Wait untill a data is available

   while((UCSRA & (1<<RXC)) == 0)
   {
      //Do nothing
   }

   //Now USART has got data from host
   //and is available is buffer
   char c = UDR;
   
	    USARTWriteChar(c);
   return c;
}





void send(unsigned char sw, unsigned char channel, unsigned char on) //, unsigned char c
{
	DDRC = 0;
	DDRD = 0;


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


int main(void)
{
char ByteReceived= 'z';


	PORTD = 0;
	PORTC = 0;



	serial_init();
      while (!(UCSRA & (1 << UDRE))) {}; // Do nothing until UDR is ready for more data to be written to it

      UDR = ByteReceived; // Echo back the received byte back to the computer
 

   while(1)// Loop forever
   {
      while (!(UCSRA & (1 << RXC))) {}; // Do nothing until data have been recieved and is ready to be read from UDR

      ByteReceived = UDR; // Fetch the recieved byte value into the variable "ByteReceived"
      ByteReceived = UDR;
      while (!(UCSRA & (1 << UDRE))) {}; // Do nothing until UDR is ready for more data to be written to it

      UDR = ByteReceived; // Echo back the received byte back to the computer
 } 


   while(1)
   {
      ByteReceived=USARTReadChar();


      USARTWriteChar(ByteReceived);

			switch(ByteReceived)
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
				send(SW2, CHANB, 0);
				break;
			}
					
	}











//	DDRD |= (1 << TX_EN);


//	DDRC = (1 << CHANA) | (1 << SW2);



}



