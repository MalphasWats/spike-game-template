#include <avr/io.h>

#include "main.h"

word t = 0;
word btn_timer = 0;

int main (void) 
{    
    initialise();
        
    // Display Logo
    // 52 * 128
    for(word pixel=0 ; pixel < 52*128 ; pixel++)
    {
        shift_out_byte(PALETTE[12]);
        shift_out_byte(PALETTE[12]>>8);
    }
    
    // 16 + logo + 16
    for(byte row=0 ; row<24 ; row++)
    {
        for(byte i=0 ; i<16 ; i++)
        {
            shift_out_byte(PALETTE[12]);
            shift_out_byte(PALETTE[12]>>8);
        }
        for(byte pixel=0 ; pixel<96 ; pixel++)
        {
            shift_out_byte(PALETTE[LOGO[row*96+pixel]]);
            shift_out_byte(PALETTE[LOGO[row*96+pixel]]>>8);
        }
        for(byte i=0 ; i<16 ; i++)
        {
            shift_out_byte(PALETTE[12]);
            shift_out_byte(PALETTE[12]>>8);
        }
    }
    
    // 52 * 128
    for(word pixel=0 ; pixel < 52*128 ; pixel++)
    {
        shift_out_byte(PALETTE[12]);
        shift_out_byte(PALETTE[12]>>8);
    }
    
    delay_ms(SPLASH_DELAY);
    
    for(ever)
    {
        t = millis();
        
        if (btn_timer == 0)
        {
            if (PINC > 0)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
        }
        
        if (t >= btn_timer)
            btn_timer = 0;
        
    }
}
