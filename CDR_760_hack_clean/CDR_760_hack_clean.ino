#include <SPI.h>

volatile bool outputRequired = false;
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
  if (SPDR == 0x0A){ // If this is the block of 4 bytes that we are interested in
    outputRequired = true;  
  }
}

  // end of interrupt service routine (ISR) SPI_STC_vect
void loop() {
 if (outputRequired){
    timerStart = micros();
    outputTrigger = true;
    outputRequired = false;
 }
 if(outputTrigger && micros() - timerStart >= 24){
    PORTB |= _BV(PB1);
    delayMicroseconds(4);
    PORTB &= ~_BV(PB1);
    outputTrigger = false;
 }
}
