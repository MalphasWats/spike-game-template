#include <avr/io.h>

#include "main.h"

word t = 0;
word btn_timer = 0;

int main (void) 
{    
    initialise();
        
    // display logo
    for(byte y=0 ; y<LOGO_HEIGHT ; y++)
        for(byte x=0 ; x<LOGO_WIDTH ; x++)
            buffer[(y+2)*SCREEN_WIDTH + (x+16)] = LOGO[y*LOGO_WIDTH + x];
    
    delay_ms(SPLASH_DELAY);
    
    for(ever)
    {
        t = millis();
        
        if (btn_timer == 0)
        {
            if (~PINC > 0)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
        }
        
        if (t >= btn_timer)
            btn_timer = 0;
        
    }
}
