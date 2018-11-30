#ifndef SPIKE_H
# define SPIKE_H

#define F_CPU 8000000

#define ever ;;

#define LOW     0
#define HIGH    1

#define TRUE    0xFF
#define FALSE   0x00

#define SND   5  // PORTD

/* Display Pins (PORTB) */
#define CS      1
#define DC      3
#define RST     2

#define SCK     0

/* Display Pins (PORTD) */
#define MOSI    1

/* Button Pins (PORTC) */
#define UP          6
#define DOWN        5
#define LEFT        4
#define RIGHT       3
#define BTN_A       2
#define BTN_B       1
#define BTN_C       0

/* Button Masks */
#define B_UP        0b01000000
#define B_DOWN      0b00100000
#define B_LEFT      0b00010000
#define B_RIGHT     0b00001000
#define B_A         0b00000100
#define B_B         0b00000010
#define B_C         0b00000001

#define BTN_DELAY       180

#define SPLASH_DELAY    1500

#define CMD             LOW
#define DATA            HIGH

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64

#define SCREEN_COLUMNS  16
#define SCREEN_ROWS     8

// http://www.soundoctor.com/freq.htm
//      NOTE    PERIOD   FREQ.  Note        
#define _A4    2270/2 // 440hz, Concert A(4)  0
#define _Bb4   2100/2 // 466hz, Bb(4)         1
#define _B4    2000/2 // 494hz, B(4)          2
#define _C5    1900/2 // 523hz, C(5)          3
#define _Cs5   1800/2 // 554hz, C#(5)         4
#define _D5    1700/2 // 587hz, D(5)          5
#define _Ds5   1600/2 // 622hz, D#(5)         6
#define _E5    1500/2 // 659hz, E(5)          7
#define _F5    1400/2 // 698hz, F(5)          8
#define _Fs5   1350/2 // 740hz, F#(5)         9
#define _G5    1280/2 // 748hz, G(5)          A
#define _Gs5   1200/2 // 831hz, G#(5)         B
#define _A5    1140/2 // 800 A(5)             C
#define _Bb5   1070/2 // 932, Bb(5)           D
#define _B5    1010/2 // 988, B(5)            E
#define _A8    142/2  // 7040                 F
#define _A9    71/2   // 14080hz             X

typedef unsigned char byte;
typedef unsigned int word;

byte buffer[SCREEN_WIDTH * SCREEN_ROWS];

static const __flash byte LOGO[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x78, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 
    0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 0xff, 0x0e, 0xff, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x17, 0x18, 0x18, 0x18, 0x18, 0x08, 0x10, 0x18, 0x18, 0x18, 0x18, 0xd0, 0xe0, 0x00, 0x00, 0xef, 0xd7, 0x18, 0x18, 0x18, 0x18, 0x08, 0x10, 0x18, 0x18, 0x18, 0x18, 0x17, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0xd7, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0xc3, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0xd7, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x17, 0x0f, 0x00, 0x00, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x17, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x10, 0x00, 0x00, 
};

#define LOGO_WIDTH 96
#define LOGO_HEIGHT 24/8

#define rngM 7919
#define rngA 17
#define rngC 3
word rng( void );

void delay_ms( word ms );
void delay_us( word us );

// http://www.oz4.us/2015/12/recoding-bare-millis-clock-on-avr.html
// https://github.com/sourceperl/millis/blob/master/millis.c
// https://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-timers?page=all
void initialise( void );
word millis( void );

/* OLED Function */
void shift_out_byte(byte val);

void initialise_oled(void);
void clear_display(void);
void display_off(void);
void display_on(void);

void pause_drawing(void);
void resume_drawing(void);

void beep(word note, word dur);
void click( void );

#endif