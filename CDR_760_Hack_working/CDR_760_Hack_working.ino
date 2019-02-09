#include <SPI.h>

volatile byte c = 0;

void setup() {
  // turn on SPI in slave mode
  SPCR = (1<<SPIE)|(1<<SPE)|(0<<DORD)|(0<<MSTR)|(1<<CPOL)|(0<<CPHA)|(0<<SPR1)|(0<<SPR0);


 pinMode(6, OUTPUT); // Enable the override pin
 
}
// SPI interrupt routine
ISR (SPI_STC_vect)
{
  if (SPDR == 0x0A){ // If this is the block of 4 bytes that we are interested in

    // 'Do nothing' until we get to the second bit in the third byte
    digitalWrite(6, LOW);
    digitalWrite(6, LOW);
    digitalWrite(6, LOW);
    digitalWrite(6, LOW);
    digitalWrite(6, LOW);
    digitalWrite(6, LOW);
    digitalWrite(6, LOW);

    digitalWrite(6, HIGH); // Output a 1
    digitalWrite(6, LOW); // Turn off override pin
  }
}

  // end of interrupt service routine (ISR) SPI_STC_vect
void loop() {
 
}
