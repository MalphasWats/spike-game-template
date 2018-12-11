#include <avr/io.h>

#include "main.h"

#define GRAVITY 1

word t = 0;

sprite player = {
    .x=0, .y=0,
    .vx=1, .vy=0,
    .jumping=FALSE,
    .glyph=2
};

void draw_map(const map __memx *m, word x, word y)
{
    byte x_offset = x & 7; // x % 8
    x >>= 3;
    
    byte y_offset = y & 7; // y % 8
    y >>= 3;
    
    byte NUM_ROWS = SCREEN_ROWS;
    if (y_offset > 0)
        NUM_ROWS += 1;
    
    byte NUM_COLS = SCREEN_COLUMNS;
    if (x_offset > 0)
        NUM_COLS += 1;
    
    for (byte row=0 ; row<NUM_ROWS ; row++)
    {
        for (byte col=0 ; col<NUM_COLS ; col++)
        {
            draw_block(&GLYPHS[m->tiles[ m->cols * (row+y) + (col+x) ]*8], col*8-x_offset, row*8-y_offset); 
        }
    }
}

void draw_sprite(sprite *s)
{
    draw_block(&GLYPHS[s->glyph*8], s->x, s->y);
}

void draw_block(const byte __memx *glyph, int x, int y)
{
    int y_ = y;
    
    if (y < 0)
        y_ = 0-y;
        
    int block_start = ((y_ >> 3) * SCREEN_WIDTH) + x;
    
    byte y_offset_a = y & 7; // y % 8
    byte y_offset_b = 8-y_offset_a;
    
    byte glyph_index = 0;
    byte block_width = 8;
    if (x < 0)
    {
        block_start -= x;
        glyph_index = 0-x;
        block_width -= glyph_index;
    }
    
    if (x > 120)
    {
        block_width = 128-x;
    }
    
    if (y < 0)
    {
        y_offset_a = 8;
        y_offset_b = 0-y;
        block_start -= SCREEN_WIDTH;
    }
    
    if (y > 56)
    {
        y_offset_b = 8;
    }
    
    for(byte block_offset=0 ; block_offset<block_width ; block_offset++, glyph_index++)
    {
        if (y_offset_a < 8)
            buffer[block_start+block_offset] |= glyph[glyph_index] << y_offset_a;
        if (y_offset_b < 8)
            buffer[block_start+SCREEN_WIDTH+block_offset] |= glyph[glyph_index] >> y_offset_b;
    }
}

byte check_collision(sprite *s, const __memx map *m)
{
    // TODO: Doesn't work if map drawn offset
    word col = (s->x + 4) >> 3;
    word row = (s->y + 8) >> 3;
    
    if (m->tiles[row*m->cols+col] > 0)
        return TRUE;
    return FALSE;
}

int main (void) 
{    
    initialise();
        
    // display logo
    for(byte y=0 ; y<LOGO_HEIGHT ; y++)
        for(byte x=0 ; x<LOGO_WIDTH ; x++)
            buffer[(y+2)*SCREEN_WIDTH + (x+16)] = LOGO[y*LOGO_WIDTH + x];
    draw();
    
    note(_A4, 90);
    delay_ms(180);
    note(_C5, 60);
    delay_ms(120);
    note(_E5, 60);
    
    delay_ms(SPLASH_DELAY);
    
    byte buttons = 0;
    
    /* Debugging */
    byte delta = 0;
    byte count = 0;
    sprite d0 = {.x=8*3, .y=0, .glyph=6};
    sprite d1 = {.x=8*2, .y=0, .glyph=6};
    sprite d2 = {.x=8*1, .y=0, .glyph=6};
    
    for(ever)
    {
        t = millis();
        
        buttons = ~PINC;
        if (buttons & _LEFT)
        {
            player.x -= player.vx;
            if (check_collision(&player, &level_1))
                player.x += player.vx;
        }
        if (buttons & _RIGHT)
        {
            player.x += player.vx;
            if (check_collision(&player, &level_1))
                player.x -= player.vx;
        }
        
        if ( (buttons & _A) && !player.jumping )
        {
            player.vy = -7;
            player.jumping = TRUE;
            note(_A9, 8);
        }
        player.vy += GRAVITY;
        
        player.y += player.vy;
        if (check_collision(&player, &level_1))
        {
            player.y -= player.vy;
            player.vy = 0;
            player.jumping = FALSE;
        }
        
        if (player.x < 0)
            player.x = 0;
        if (player.x > 128-8)
            player.x = 128-8;
            
        if (player.y < 0)
            player.y = 0;
        if (player.y > 64-8)
            player.y = 64-8;
            
        clear_buffer();
        
        draw_map(&level_1, 0, 0);
        
        draw_sprite(&player);
        
        draw_sprite(&d0);
        draw_sprite(&d1);
        draw_sprite(&d2);
        
        draw();
        
        /* Debugging */
        delta = (millis() - t);
        if (count == 0)
        {
            d0.glyph = (delta % 10) + 6;
            delta /= 10;
            d1.glyph = (delta % 10) + 6;
            delta /= 10;
            d2.glyph = (delta % 10) + 6;
            count = 12;
        }
        count -= 1;
    }
}
