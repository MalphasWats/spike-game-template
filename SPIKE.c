#include "SPIKE.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

word _millis = 0;

word rngSEED = 5;
word rng( void )
{
    rngSEED = (rngSEED*rngA +rngC) % rngM;
    return rngSEED;
}

void delay_ms( word ms )
{
   for (word i=0; i < ms; i++)
   {
      _delay_ms(1);
   }
}

void delay_us( word us )
{
   for (word i=0; i < us; i++)
   {
      _delay_us(1);
   }
}

void initialise( void )
{
    /* Configure Outputs */
    //DDRA
    DDRB = (1<<CS) | (1<<DC) | (1<<RST) | (1<<SCK) | (1<<MOSI);
    
    // (0<<UP) | (0<<DOWN) | (0<<LEFT) | (0<<RIGHT) | (0<<BTN_A) | (0<<BTN_B) | (0<<BTN_C); // INPUTS!
    DDRC = 128; // PC7 Unused, set as output.
    
    DDRD = (1 << SND);
    
    /* Initialise Timer */
    TCCR0A = 0x02;          // OC0A disconnected, CTC Mode.
    TCCR0B = 0x03;          // 1/64 CLK Prescale.
    
    TIMSK0 |= 0x02;         // Enable OCIEA Compare Interrupt
    
    sei();                  // Enable interrupts
    
                 //                     F_CPU   Prescale  Timer frequency (1 ms)
    OCR0A = 250; // Set compare value (16000000Hz / 64) / 1000Hz
    
    /* Setup Display */
    initialise_oled();
    clear_display();
}

ISR(TIMER0_COMPA_vect)
{
    _millis += 1;
}

word millis( void )
{
    return _millis;
}

/* OLED Functions */

void shift_out_byte(byte b)
{
    if ( b & (1 << 7) )
    {
        PORTB |= 1 << MOSI;
    }
    else
    {
        PORTB &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 6) )
    {
        PORTB |= 1 << MOSI;
    }
    else
    {
        PORTB &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 5) )
    {
        PORTB |= 1 << MOSI;
    }
    else
    {
        PORTB &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 4) )
    {
        PORTB |= 1 << MOSI;
    }
    else
    {
        PORTB &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 3) )
    {
        PORTB |= 1 << MOSI;
    }
    else
    {
        PORTB &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 2) )
    {
        PORTB |= 1 << MOSI;
    }
    else
    {
        PORTB &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 1) )
    {
        PORTB |= 1 << MOSI;
    }
    else
    {
        PORTB &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 0) )
    {
        PORTB |= 1 << MOSI;
    }
    else
    {
        PORTB &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
}

void initialise_oled(void)
{
    // SET CS LOW
    PORTB &= ~(1 << CS);        // LOW (Enabled)
    
    // TOGGLE RESET high/low/high
    PORTB |= 1 << RST;          // HIGH
    delay_ms(200);
    PORTB &= ~(1 << RST);       // LOW
    delay_ms(200);
    PORTB |= 1 << RST;          // HIGH
    delay_ms(200);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xFD);       // Command Lock
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x12);  
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xFD);       // Command Lock
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0xB1);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xA4);       // Display ALL OFF

    shift_out_byte(0xB3);       // Clock Div
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0xF1);  		// 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xCA);       // MUX Ratio
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(127);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xA0);       // SET Remap    //TODO: Need to upsidedown
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x74);       // 0111 0100
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0x15);       // SET Column
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x00);
    shift_out_byte(0x7F);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0x75);       // SET Row
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x00);
    shift_out_byte(0x7F);

    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xA1);       // Startline
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x00);

    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xA2);       // Display Offset
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x00);

    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xB5);       // SET GPIO
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x00);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xAB);       // Function Select
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x01);       // internal (diode drop)

    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xB1);       // Precharge
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x32);
 
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xBE);       // VCOMH
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x05);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xC1);       // Contrast ABC
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0xC8);
    shift_out_byte(0x80);
    shift_out_byte(0xC8);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xC7);       // Contrast Master
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x0F);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xB4);       // SET VSL
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0xA0);
    shift_out_byte(0xB5);
    shift_out_byte(0x55);
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xB6);       // Precharge
    PORTB |= 1 << DC;           // HIGH (DATA)
    shift_out_byte(0x01);
    
    //PORTB &= ~(1 << DC);        // LOW (COMMAND)
    //shift_out_byte(0xA5);       // Display ALL On
    
    PORTB &= ~(1 << DC);        // LOW (COMMAND)
    shift_out_byte(0xA6);       // Normal Display (not inverted)
    
    shift_out_byte(0x5C);       // Write RAM
    
    PORTB |= 1 << DC;           // DATA
}

void clear_display(void)
{
    for (word pixel=0 ; pixel<SCREEN_HEIGHT*SCREEN_WIDTH ; pixel++)
    {
        shift_out_byte(0x00);
        shift_out_byte(0x00);
    }
}

void display_off(void)
{
    PORTB &= ~(1 << DC);        // COMMAND
    shift_out_byte(0xAE);       // DISPLAYOFF (Sleep)
    
    shift_out_byte(0x5C);       // Write RAM
    
    PORTB |= 1 << DC;           // DATA
}

void display_on(void)
{
    PORTB &= ~(1 << DC);        // COMMAND
    shift_out_byte(0xAF);       // DISPLAYON (Wake)
    
    shift_out_byte(0x5C);       // Write RAM
    
    PORTB |= 1 << DC;           // DATA
}

/* Sound Functions */

void beep(word note, word dur)
{
    word ts = millis() + dur;
    while (millis() < ts)
    {
        PORTD |= 1 << SND;      // HIGH
        delay_us(note);
        PORTD &= ~(1 << SND);   // LOW
        delay_us(note);
    }
}

void click( void )
{
    beep(_A9, 15);
}