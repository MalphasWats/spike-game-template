#include <avr/io.h>

#include "main.h"

word t = 0;
word btn_timer = 0;

sprite player = {
    .x=0, .y=0,
    .frame=0,
    .frame_duration=100,
    .animation_length=2,
    .animation_timer=0,
    .frames = {2, 3}
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
            buffer[col*8+0] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 0];
            buffer[col*8+1] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 1];
            buffer[col*8+2] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 2];
            buffer[col*8+3] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 3];
            buffer[col*8+4] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 4];
            buffer[col*8+5] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 5];
            buffer[col*8+6] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 6];
            buffer[col*8+7] = GLYPHS[map->tiles[ map->cols * (row+y) + (col+x) ]*8 + 7];
        }
    }
}

void draw_sprite(sprite *s)
{
    //word col = s->x >> 3;
    word row = s->y >> 3;
    
    //byte y_offset = row % 8; //TODO: Can this be faster?
    byte y_offset = row & 7; // row % 8
    
    buffer[(row*SCREEN_WIDTH + s->x)+0] |= GLYPHS[s->frames[s->frame]*8+0] >> y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+1] |= GLYPHS[s->frames[s->frame]*8+1] >> y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+2] |= GLYPHS[s->frames[s->frame]*8+2] >> y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+3] |= GLYPHS[s->frames[s->frame]*8+3] >> y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+4] |= GLYPHS[s->frames[s->frame]*8+4] >> y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+5] |= GLYPHS[s->frames[s->frame]*8+5] >> y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+6] |= GLYPHS[s->frames[s->frame]*8+6] >> y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+7] |= GLYPHS[s->frames[s->frame]*8+7] >> y_offset;
    
    if (y_offset > 0)
    {
        buffer[((row+1)*SCREEN_WIDTH + s->x)+0] |= GLYPHS[s->frames[s->frame]*8+0] << (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+1] |= GLYPHS[s->frames[s->frame]*8+1] << (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+2] |= GLYPHS[s->frames[s->frame]*8+2] << (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+3] |= GLYPHS[s->frames[s->frame]*8+3] << (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+4] |= GLYPHS[s->frames[s->frame]*8+4] << (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+5] |= GLYPHS[s->frames[s->frame]*8+5] << (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+6] |= GLYPHS[s->frames[s->frame]*8+6] << (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+7] |= GLYPHS[s->frames[s->frame]*8+7] << (8-y_offset);
    }
}

int main (void) 
{    
    initialise();
        
    // display logo
    for(byte y=0 ; y<LOGO_HEIGHT ; y++)
        for(byte x=0 ; x<LOGO_WIDTH ; x++)
            buffer[(y+2)*SCREEN_WIDTH + (x+16)] = LOGO[y*LOGO_WIDTH + x];
    
    delay_ms(SPLASH_DELAY);
    
    byte buttons = 0;
    
    for(ever)
    {
        t = millis();
        
        if (btn_timer == 0)
        {
            buttons = ~PINC;
            if (buttons & B_A)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
        }
        
        if (t >= btn_timer)
            btn_timer = 0;
        
        draw_map(&level_1, 0, 0);
        
        draw_sprite(&player);
    }
}
