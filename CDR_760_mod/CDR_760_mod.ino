#include <SPI.h>

volatile bool outputRequired = false; // Flag set in the interrupt
bool outputTrigger = false;
long timerStart = 0;

void setup() {
  // turn on SPI in slave mode
  SPCR = (1<<SPIE)|(1<<SPE)|(0<<DORD)|(0<<MSTR)|(1<<CPOL)|(0<<CPHA)|(0<<SPR1)|(0<<SPR0);

 pinMode(9, OUTPUT); // Enable the override pin
 
}
// SPI interrupt routine
ISR (SPI_STC_vect)
{
  if (SPDR == 0x0A){ // If this is the block of 4 bytes that we are interested in...
    outputRequired = true; // ...need to overwrite the third byte
  }
}

  // end of interrupt service routine (ISR) SPI_STC_vect
void loop() {
 if (outputRequired){ // If the block of data we are interested in has been found...
    timerStart = micros(); // ...start the timer to countown to when we need to output a signal
    outputTrigger = true;
    outputRequired = false; // reset flag
 }
 if(outputTrigger && micros() - timerStart >= 24){ // When we need to output the signal...
    PORTB |= _BV(PB1); // output the signal
    delayMicroseconds(4); 
    PORTB &= ~_BV(PB1); // turn off signal
    outputTrigger = false; // reset flag
 }
}
