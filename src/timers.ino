#include <avr/io.h>
#include <avr/interrupt.h>

/*
 * https://learn.adafruit.com/multi-tasking-the-arduino-part-2/interrupt-etiquette
One interrupt at a time.

When in the ISR, interrupts are disabled.  This has two very important implications:

    Work done in the ISR should be kept short so as not to miss any interrupts.
    Code in the ISR should not call anything that requires interrupts to be active (e.g. delay() or anything that uses the i2c bus).  This will result in hanging your program

    
    Timer0 - used for millis(), micros(), delay() and PWM on pins 5 & 6
    Timer1 - used for Servos, the WaveHC library and PWM on pins 9 & 10
    Timer2 - used by Tone and PWM on pins 11 & 13

*/
    
// byte varCompteur = 0; // La variable compteur
 
//#define LEDPIN 2
 
 /// taken from http://www.engblaze.com/microcontroller-tutorial-avr-and-arduino-timer-interrupts/
 
//******************************************************************
//Timer0:
// Timer0 is a 8bit timer.
// In the Arduino world Timer0 is been used for the timer functions, like delay(), millis() and micros(). If you change Timer0 registers, this may influence the Arduino timer function. So you should know what you are doing.
//Timer1:
// Timer1 is a 16bit timer.
// In the Arduino world the Servo library uses Timer1 on Arduino Uno (Timer5 on Arduino Mega).
//Timer2:
// Timer2 is a 8bit timer like Timer0.
// In the Arduino work the tone() function uses Timer2
// ATmega168, ATmega328:
// - Using Timer 1 disables PWM (analogWrite) on pins 9 and 10 - 16bit
// ATmega2560:
// - Using Timer 1 disables PWM (analogWrite) on pins 11 and 12 - 16bit
// - Using Timer 3 disables PWM (analogWrite) on pins 2, 3 and 5 - 16bit
// - Using Timer 4 disables PWM (analogWrite) on pins 6, 7 and 8- 16bit
// - Using Timer 5 disables PWM (analogWrite) on pins 44, 45 and 46 - 16bit
//******************************************************************



void setup_timer1() //1 second intervall
{
  //http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html

         if(serial_debug){
          Serial.println(F("Setup timer"));
        }

  // TIMER 1 for interrupt frequency 1 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 1 Hz increments
  OCR1A = 62499; // = 16000000 / (256 * 1) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  //TIMSK1 |= (1 << OCIE1A);
  TIMSK1 |= _BV (OCIE1A);
  sei(); // allow interrupts
}


ISR(TIMER1_COMPA_vect)
{
  //run_every_1_sec();
  need_refresh = true;
}
