#include "SPIKE.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile word _millis = 0;

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
    DDRB = (1<<CS) | (1<<DC) | (1<<RST) | (1<<SCK);
    
    PORTC = 0xFF; // Set pull-up resistors
    
    DDRD = (1 << SND) | (1<<MOSI);
    
    /* Initialise "millis" Timer */
    TCCR0A = 0x02;          // OC0A disconnected, CTC Mode.
    TCCR0B = 0x03;          // 1/64 CLK Prescale.
    
                 //                     F_CPU   Prescale  Timer frequency (1 ms)
    OCR0A = 125; // Set compare value (8000000Hz / 64) / 1000Hz
    //OCR0A = 250; // Set compare value (16000000Hz / 64) / 1000Hz
    
    TIMSK0 |= 0x02;         // Enable OCR0A Compare Interrupt
    
    
    /* Initialise "draw" Timer */
    TCCR2A = 0x02;          // OC2A disconnected, CTC Mode.
    TCCR2B = 0x07;          // 1/1024 CLK Prescale.
    
                 //                     F_CPU   Prescale   Timer frequency (1 ms)
    //OCR2A = 231; // Set compare value ((8000000Hz / 1024) / 1000Hz) * 33  // 30fps
    // TODO: Need to time interrupt duration and tweak this number
    // TODO: for now just fudge it a bit
    OCR2A = 210; // ~3 ms to push out the screen data, probably actually faster than that though.
    
    sei();                  // Enable interrupts
    
    /* Setup Display */
    initialise_oled();
    
    // Need to do this AFTER display initialisation otherwise
    // The interrupt will fire and write garbage into command registers!
    TIMSK2 = 0x02;          // Enable OCR2A Interrupt
    
    clear_display();
}

ISR(TIMER0_COMPA_vect)
{
    _millis += 1;
}

ISR(TIMER2_COMPA_vect)
{
    for (word i=0 ; i<SCREEN_WIDTH*SCREEN_ROWS ; i++)
    {
        shift_out_byte(buffer[i]);
    }
}

word millis( void )
{
    return _millis;
}

/* OLED Functions */

// TODO: this should use HW SPI (pins configured for USART SPI)
void shift_out_byte(byte b)
{
    if ( b & (1 << 7) )
    {
        PORTD |= 1 << MOSI;
    }
    else
    {
        PORTD &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 6) )
    {
        PORTD |= 1 << MOSI;
    }
    else
    {
        PORTD &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 5) )
    {
        PORTD |= 1 << MOSI;
    }
    else
    {
        PORTD &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 4) )
    {
        PORTD |= 1 << MOSI;
    }
    else
    {
        PORTD &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 3) )
    {
        PORTD |= 1 << MOSI;
    }
    else
    {
        PORTD &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 2) )
    {
        PORTD |= 1 << MOSI;
    }
    else
    {
        PORTD &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 1) )
    {
        PORTD |= 1 << MOSI;
    }
    else
    {
        PORTD &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
    
    if ( b & (1 << 0) )
    {
        PORTD |= 1 << MOSI;
    }
    else
    {
        PORTD &= ~(1 << MOSI);
    }
    
    PORTB |= 1 << SCK;      // HIGH
    PORTB &= ~(1 << SCK);   // LOW
}

/* Initiasation for SSD1306 OLED Controller */
void initialise_oled(void)
{
    PORTB &= ~(1 << DC);                // LOW (Command Mode)
    
    PORTB |= 1 << RST;          // HIGH
    delay_ms(10);
    PORTB &= ~(1 << RST);       // LOW
    delay_ms(10);
    PORTB |= 1 << RST;          // HIGH
    delay_ms(10);
    
    shift_out_byte(0xAE);               // DISPLAYOFF
    
    shift_out_byte(0xD5);               // SETDISPLAYCLOCKDIV
    shift_out_byte(0x80);               // the suggested ratio 0x80

    shift_out_byte(0xA8 );              // SSD1306_SETMULTIPLEX
    shift_out_byte(SCREEN_HEIGHT - 1);

    shift_out_byte(0xD3 );              // SETDISPLAYOFFSET
    shift_out_byte(0x0);                // no offset
    shift_out_byte(0x40  | 0x0);        // SETSTARTLINE line #0
  
    shift_out_byte(0x8D);               // CHARGEPUMP
    shift_out_byte(0x14);               // Not External Vcc
  
    shift_out_byte(0x20 );              // MEMORYMODE
    shift_out_byte(0x00);               // 0x0 act like ks0108
    shift_out_byte(0xA0  | 0x1);        // SEGREMAP
    shift_out_byte(0xC8 );              // COMSCANDEC


    shift_out_byte(0xDA);               // SETCOMPINS
    shift_out_byte(0x12);
  
    shift_out_byte(0x81 );              // SETCONTRAST
    shift_out_byte(0xCF);               // Not External Vcc


    shift_out_byte(0xD9 );              // SETPRECHARGE
    shift_out_byte(0xF1);               // Not External Vcc
  
    shift_out_byte(0xDB);               // SETVCOMDETECT
    shift_out_byte(0x40);
  
    shift_out_byte(0xA4 );              // DISPLAYALLON_RESUME
    shift_out_byte(0xA6 );              // NORMALDISPLAY

    //shift_out_byte(0x2E );            // DEACTIVATE_SCROLL

    shift_out_byte(0xAF);               // DISPLAYON
    
    shift_out_byte(0xB0 + 0);           // PAGEADDR (0 = reset)
    shift_out_byte(0 & 0x0F);           // Column start address (0 = reset)
    shift_out_byte(0x10 | (0 >> 4));    // LOW COL ADDR
    
    PORTB |= 1 << DC;                   // DATA
}

void clear_display(void)
{
    for (word i=0 ; i<SCREEN_WIDTH*SCREEN_ROWS ; i++)
    {
        buffer[i] = 0x00;
        //shift_out_byte(0x00);
    }
}

void pause_drawing(void)
{
    TIMSK2 = 0x00;
}

void resume_drawing(void)
{
    TIMSK2 = 0x02;
}


void display_off(void)
{
    pause_drawing();
    PORTB &= ~(1 << DC);        // COMMAND
    shift_out_byte(0xAE);       // DISPLAYOFF
    
    PORTB |= 1 << DC;           // DATA
}

void display_on(void)
{
    PORTB &= ~(1 << DC);        // COMMAND
    shift_out_byte(0xAF);       // DISPLAYON
    
    PORTB |= 1 << DC;           // DATA
    resume_drawing();
}

void display_image(const byte __memx *image, byte x, byte y, byte width, byte height)
{
    // TODO: Needs to handle coords not on grid
    height >>= 3;
    y >>= 3;
    
    
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