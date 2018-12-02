#include <avr/io.h>

#include "main.h"

word t = 0;

sprite player = {
    .x=0, .y=0,
    .frame=2
};

void draw_map(const map __memx *map, word x, word y)
{
    // TODO: Need to allow x & y to cross block boundaries
    x >>= 3;
    y >>= 3;
    
    for (byte row=0 ; row<SCREEN_ROWS ; row++)
    {
        for (byte col=0 ; col<SCREEN_COLUMNS ; col++)
        {
            buffer[(row*SCREEN_WIDTH)+col*8+0] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 0];
            buffer[(row*SCREEN_WIDTH)+col*8+1] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 1];
            buffer[(row*SCREEN_WIDTH)+col*8+2] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 2];
            buffer[(row*SCREEN_WIDTH)+col*8+3] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 3];
            buffer[(row*SCREEN_WIDTH)+col*8+4] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 4];
            buffer[(row*SCREEN_WIDTH)+col*8+5] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 5];
            buffer[(row*SCREEN_WIDTH)+col*8+6] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 6];
            buffer[(row*SCREEN_WIDTH)+col*8+7] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 7];
        }
    }
}

void draw_sprite(sprite *s)
{
    //word col = s->x >> 3;
    word row = s->y >> 3;
    byte y_offset = s->y & 7; // s->y % 8
    
    buffer[(row*SCREEN_WIDTH + s->x)+0] |= GLYPHS[s->frame*8+0] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+1] |= GLYPHS[s->frame*8+1] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+2] |= GLYPHS[s->frame*8+2] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+3] |= GLYPHS[s->frame*8+3] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+4] |= GLYPHS[s->frame*8+4] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+5] |= GLYPHS[s->frame*8+5] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+6] |= GLYPHS[s->frame*8+6] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+7] |= GLYPHS[s->frame*8+7] << y_offset;
    
    if (y_offset > 0)
    {
        buffer[((row+1)*SCREEN_WIDTH + s->x)+0] |= GLYPHS[s->frame*8+0] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+1] |= GLYPHS[s->frame*8+1] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+2] |= GLYPHS[s->frame*8+2] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+3] |= GLYPHS[s->frame*8+3] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+4] |= GLYPHS[s->frame*8+4] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+5] |= GLYPHS[s->frame*8+5] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+6] |= GLYPHS[s->frame*8+6] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+7] |= GLYPHS[s->frame*8+7] >> (8-y_offset);
    }
}

int main (void) 
{    
    initialise();
        
    // display logo
    for(byte y=0 ; y<LOGO_HEIGHT ; y++)
        for(byte x=0 ; x<LOGO_WIDTH ; x++)
            buffer[(y+2)*SCREEN_WIDTH + (x+16)] = LOGO[y*LOGO_WIDTH + x];
    flip();
    //beep(_A4, 60);
    //delay_ms(30);
    //beep(_C5, 45), 
    //delay_ms(20);
    //beep(_E5, 30);
    
    delay_ms(SPLASH_DELAY);
    
    byte buttons = 0;
    //byte cnt = 100;
    byte delta = 0;
    //word timer = 0;
    //byte tmp = 0;
    sprite d0 = {.x=8*3, .y=0, .frame=6};
    sprite d1 = {.x=8*2, .y=0, .frame=6};
    sprite d2 = {.x=8*1, .y=0, .frame=6};
    
    for(ever)
    {
        t = millis();
        
        buttons = ~PINC;
        if (buttons & B_LEFT)
        {
            player.x -= 1;
        }
        if (buttons & B_RIGHT)
        {
            player.x += 1;
        }
        if (buttons & B_UP)
        {
            player.y -= 1;
        }
        if (buttons & B_DOWN)
        {
            player.y += 1;
        }
        
        if (player.x < 0)
            player.x = 0;
        if (player.x > 128-8)
            player.x = 128-8;
            
        if (player.y < 0)
            player.y = 0;
        if (player.y > 64-8)
            player.y = 64-8;
        
        draw_map(&level_1, 0, 0);
        
        draw_sprite(&player);
        
        draw_sprite(&d0);
        draw_sprite(&d1);
        draw_sprite(&d2);
        
        flip();
        
        //timer = millis();
        
        //for (word i=0 ; i<SCREEN_WIDTH*SCREEN_ROWS ; i++)
        //{
        //    shift_out_byte(buffer[i]);
        //}
        
        //cnt += 1;
        //if (cnt == 100)
        //{
            
            delta = (millis() - t);///100;
            //timer = millis();
            
            //cnt = 0;
            
            d0.frame = (delta % 10) + 6;
            delta /= 10;
            d1.frame = (delta % 10) + 6;
            delta /= 10;
            d2.frame = (delta % 10) + 6;
        //}
            
        
    }
}
