#include <Arduino.h>
#line 1 "C:\\Users\\Sriya\\Documents\\Arduino\\led\\led.ino"
int count=0;

#define F_CPU 12000000UL // Defining the CPU Frequency

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Generates a Blocking Delay
#include<string.h>
#define USART_BAUDRATE 2400 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 12UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

#line 28 "C:\\Users\\Sriya\\Documents\\Arduino\\led\\led.ino"
void USART_Init();
#line 41 "C:\\Users\\Sriya\\Documents\\Arduino\\led\\led.ino"
char USART_ReceivePolling();
#line 48 "C:\\Users\\Sriya\\Documents\\Arduino\\led\\led.ino"
void USART_TransmitPolling(char DataByte);
#line 53 "C:\\Users\\Sriya\\Documents\\Arduino\\led\\led.ino"
void USART_Send_String( char *s);
#line 60 "C:\\Users\\Sriya\\Documents\\Arduino\\led\\led.ino"
int main();
#line 28 "C:\\Users\\Sriya\\Documents\\Arduino\\led\\led.ino"
void USART_Init()
{
  // Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

char USART_ReceivePolling()
{
	char DataByte;
	while (( UCSR0A & (1<<RXC0)) == 0) {}; // Do nothing until data have been received
	DataByte = UDR0 ;
	return DataByte;
}
void USART_TransmitPolling(char DataByte)
{
	while (( UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
	UDR0 = DataByte;
}
void USART_Send_String( char *s){
  while(*s){
    USART_TransmitPolling(*s++);
      }
}


int main()
{
	USART_Init();
  char str[1008];
  char in =-1;
  byte index=0;
  while(index<1008){
    in = USART_ReceivePolling();
    str[index] = in; // Store it
    USART_TransmitPolling(str[index]);
    
    index++; // Increment where to write next
    count++;
    
  }
  
	str[index] = '\0';

  
	return 0;
}
