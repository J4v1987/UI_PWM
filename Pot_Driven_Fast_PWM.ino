/*
Arduino Nano potentiometer driven fast PWM implementation

Design considerations:
  G1. Nominal topology shall operate with mains 127VAC @ 60Hz.

Features:
  F1. UI-enabled PWM, based on Arduino Nano (Atmel ATMega328p).
  F2. Leverages Timer/Counter1 register to offer best hardware MCU resolution of 16bit.
  F3. Generates a fast-pwm signal on pin D9 with variable duty cycle, at nominal 120Hz, as provided hereby.
  F4. Leverages direct MCU register manipulation to efficiently adjust PWM waveform in frequency and duty-cycle.
  F5. Provides a UI consisting of a 10kΩ potentiometer to regulate duty-cycle.
  F6. Potentiometer wiper to be sampled at pin A0.
  F7. ADC registeres catch analog input A0 to adjust duty cycle register OCR1A.
  F8. PWM frequency to be adjusted with register ICR1.
  F9. Pulse width updates take place in ISR TIMER1_COMPA vector.

By: Javier.
Portfolio: https://sites.google.com/view/b-eng-jarl/home
Arduino Forums: j4v13r_987
GitHub: J4v1987

History:
  H1. Loaded to Arduino Nano V3 using Arduino IDE 2.3.6. Deemed operational as per read-me media.

Further reading:
  FR1. Atmel (2015). ATmega328P 8-bit AVR Microcontroller with 32K Bytes In-System Programmable Flash DATASHEET. [online] Available at: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf.
  FR2. Monk, S. (2017). Electronics Cookbook: Using PWM Outputs to Control Power Output. [online] https://learning.oreilly.com. Available at: https://learning.oreilly.com/videos/electronics-cookbook/ [Accessed 25 Apr. 2025].
  FR3. Scherz, Paul, and Simon Monk. “Practical Electronics for Inventors.” Https://Learning.oreilly.com, O’Reilly Media, Inc., Apr. 2016, learning.oreilly.com/library/view/practical-electronics-for. Accessed Apr. 2025. ISBN 978-1-25-958754-2, e-ISBN 978-1-25-958755-9.

Acknowledgements:
  ACK1. Harvard-style references: MyBib Contributors (2019). Harvard Referencing Generator – FREE – (updated for 2019). [online] MyBib. Available at: https://www.mybib.com/tools/harvard-referencing-generator.
  ACK2. Peer-checking and internet data scraping: Pi.ai. (2025). AVR PWM [thread]. Pi, your personal AI. [online] Available at: https://pi.ai.
  ACK3. Video editing: Kdenlive project. https://kdenlive.org/.
  ACK4. Operating system: Ubuntu. https://ubuntu.com/.

Discussions:
  DS1. Arduino Forum. (2025). Is the Timer/Counter 0 limited to prescaler of 64? [online] Available at: https://forum.arduino.cc/t/is-the-timer-counter-0-limited-to-prescaler-of-64/1376889?u=j4v13r_987 [Accessed 29 Apr. 2025].
  DS2. Dylan144GT (2018). Setting up Arduino Uno (ATMEGA328P) PWM with Timer1. [online] Stack Overflow. Available at: https://stackoverflow.com/questions/48873501/setting-up-arduino-uno-atmega328p-pwm-with-timer1.
*/

ISR(TIMER1_COMPA_vect)
{
  //Fetch ADC sample at channel number 'ch' indicated with an integer (0-7)
  unsigned long pwRaw = readADC(0);
  //Scale ADC sample to proportionally match the PWM timer/counter1 resolution of 16-bits
  OCR1A = (pwRaw*ICR1)/1023;
}

void InitADC(){
  // Disable power reduction ADC bit to enable ADC register
  PRR = (0 << PRADC);
  // Set analog reference to AVcc and right-adjust result
  ADMUX = (1 << REFS0) | (0 << REFS1) | (0 << ADLAR);
  // Enable ADC, set ADC clock prescaler to 128, and start conversion
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN) | (1 << ADSC); //scalar div factor =128
}

uint16_t readADC(uint8_t ch) {
  uint16_t adcValue;
  uint16_t lowLim=33;
  uint16_t maxLim=1023-lowLim;

  // Select ADC Channel 'ch' must be 0-7
  ch = ch & 0b00000111;
  ADMUX |= ch;
  // Start Single conversion
  ADCSRA |= (1 << ADSC);
  // Wait for conversion to complete
  while (!(ADCSRA & (1 << ADIF))) {
    // Do nothing
  }
  // Clear ADIF by writing one to it
  ADCSRA |= (1 << ADIF);
  //return ADC;  // Return the full 10-bit value
  adcValue = ADCL;
  adcValue |= (ADCH << 8);
  //ADC variable overflow prevention feature 
  if (adcValue<=lowLim) {
    adcValue = lowLim;
  }  
  else if (adcValue>=maxLim){
    adcValue = maxLim;
  }
  //output post-processed ADC value
  return adcValue;
}

void setup() {
  InitADC();
  
  // Set pin D9 as output, tied to OC1A register.
  // FR1: sec. 13.3.1, figure 1-1. 
  DDRB = (1 << DDB1);

  // Reset the timer 1 register to assure initialization for 'zero'.
  // FR1: sec. 15.2.1, figure 15-1, figure 15-7.
  TCNT1 = 0;
  
  // Set WGM mode 5, TOP compare at ICR1, toggle at OCR1A, no prescaler, .
  // FR1: sec. 15.11.1, 15.11.2, table 15-3, table 15-5, table 15-6. 
  TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (0 << WGM10);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (0 << CS11) | (1 << CS10);
  
  // FR1: sec. 15.9.3, figure 15-1, figure 15-7
  // Define PWM characteristics
  // ICR1 defines PWM frequency with a 16-bit resolution (0-65535)
  //    PWM frequency for this particular implementation
  //    is defined by formula:
  //
  //    fpwm=fmcu/(N*(1+ICR1))
  //
  // OCR1A defines pulse width duty cycle with a 16-bit resolution (0-65535)
  ICR1 = 129;
  OCR1A = 0;

  // FR1: sec. 15.11.8
  // Enable the Timer/Counter0 Output Compare A Match Interrupt (OCIE0A)
  // This may be necessary to fully enable the PWM output on OC1A/PB1
  // depending on algorithm functionality as per design requirements
  //    If required, corresponding ISR is to be defined before setup. E.g. ISR(TIMER1_COMPA_vect)
  //    else, avoid summoning TIMSK1.
  //    Note: Summoning TIMSK1 and leaving ISR underdefined may cause PWM comparators to misfire 
  TIMSK1 = (1 << OCIE1A);
}

void loop() {
  
}