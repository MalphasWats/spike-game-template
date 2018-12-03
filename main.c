#include <avr/io.h>

#include "main.h"

#define GRAVITY 1

word t = 0;

sprite player = {
    .x=0, .y=0,
    .vx=2, .vy=0,
    .jumping=FALSE,
    .glyph=2
};

void draw_map(const map __memx *m, word x, word y)
{
    // TODO: Need to allow x & y to cross block boundaries
    x >>= 3;
    y >>= 3;
    
    for (byte row=0 ; row<SCREEN_ROWS ; row++)
    {
        for (byte col=0 ; col<SCREEN_COLUMNS ; col++)
        {
            word i = (row*SCREEN_WIDTH)+col*8;
            word j = m->cols * (row+y) + (col+x) *8;
            buffer[i+0] = GLYPHS[m->tiles[ j + 0]];
            buffer[i+1] = GLYPHS[m->tiles[ j + 1]];
            buffer[i+2] = GLYPHS[m->tiles[ j + 2]];
            buffer[i+3] = GLYPHS[m->tiles[ j + 3]];
            buffer[i+4] = GLYPHS[m->tiles[ j + 4]];
            buffer[i+5] = GLYPHS[m->tiles[ j + 5]];
            buffer[i+6] = GLYPHS[m->tiles[ j+ 6]];
            buffer[i+7] = GLYPHS[m->tiles[ j + 7]];
        }
    }
}

void draw_sprite(sprite *s)
{
    word row = s->y >> 3;
    byte y_offset = s->y & 7; // s->y % 8
    
    buffer[(row*SCREEN_WIDTH + s->x)+0] |= GLYPHS[s->glyph*8+0] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+1] |= GLYPHS[s->glyph*8+1] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+2] |= GLYPHS[s->glyph*8+2] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+3] |= GLYPHS[s->glyph*8+3] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+4] |= GLYPHS[s->glyph*8+4] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+5] |= GLYPHS[s->glyph*8+5] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+6] |= GLYPHS[s->glyph*8+6] << y_offset;
    buffer[(row*SCREEN_WIDTH + s->x)+7] |= GLYPHS[s->glyph*8+7] << y_offset;
    
    if (y_offset > 0)
    {
        buffer[((row+1)*SCREEN_WIDTH + s->x)+0] |= GLYPHS[s->glyph*8+0] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+1] |= GLYPHS[s->glyph*8+1] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+2] |= GLYPHS[s->glyph*8+2] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+3] |= GLYPHS[s->glyph*8+3] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+4] |= GLYPHS[s->glyph*8+4] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+5] |= GLYPHS[s->glyph*8+5] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+6] |= GLYPHS[s->glyph*8+6] >> (8-y_offset);
        buffer[((row+1)*SCREEN_WIDTH + s->x)+7] |= GLYPHS[s->glyph*8+7] >> (8-y_offset);
    }
}

byte check_collision(sprite *s, const map __memx *m)
{
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
    flip();
    beep(_A4, 60);
    delay_ms(30);
    beep(_C5, 45);
    delay_ms(20);
    beep(_E5, 30);
    
    delay_ms(SPLASH_DELAY);
    
    byte buttons = 0;
    
    /* Debugging */
    byte delta = 0;
    sprite d0 = {.x=8*3, .y=0, .glyph=6};
    sprite d1 = {.x=8*2, .y=0, .glyph=6};
    sprite d2 = {.x=8*1, .y=0, .glyph=6};
    
    for(ever)
    {
        t = millis();
        
        buttons = ~PINC;
        if (buttons & B_LEFT)
        {
            player.x -= player.vx;
            if (check_collision(&player, &level_1))
                player.x += player.vx;
        }
        if (buttons & B_RIGHT)
        {
            player.x += player.vx;
            if (check_collision(&player, &level_1))
                player.x -= player.vx;
        }
        
        if ( (buttons & B_A) && !player.jumping )
        {
            player.vy = -7;
            player.jumping = TRUE;
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
        
        draw_map(&level_1, 0, 0);
        
        draw_sprite(&player);
        
        draw_sprite(&d0);
        draw_sprite(&d1);
        draw_sprite(&d2);
        
        flip();
        
        /* Debugging */
        delta = (millis() - t);
        d0.glyph = (delta % 10) + 6;
        delta /= 10;
        d1.glyph = (delta % 10) + 6;
        delta /= 10;
        d2.glyph = (delta % 10) + 6;
    }
}
