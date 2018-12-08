#ifndef MAIN_H
# define MAIN_H

#include "SPIKE.h"

typedef struct map {
    word cols;
    word rows;
    byte tiles[];
} map;

typedef struct sprite {
    int x;
    int y;
    
    int vx;
    int vy;
    
    byte jumping;
    
    word glyph;
} sprite;

static const __flash byte GLYPHS[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x7f, 0xaf, 0xdf, 0xaf, 0xdf, 0xaf, 0xdf, 0x7f, 
    0x00, 0x00, 0x80, 0x76, 0xf6, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0xf6, 0x76, 0xa0, 0x00, 0x00, 
    0x00, 0x00, 0x38, 0x74, 0x7c, 0x7c, 0x38, 0x00, 
    0x00, 0x00, 0x00, 0x38, 0x7c, 0x38, 0x00, 0x00, 
    
    0x00, 0x3E, 0x7F, 0x4D, 0x59, 0x7F, 0x3E, 0x00, // 0
    0x00, 0x11, 0x31, 0x7F, 0x7F, 0x01, 0x01, 0x00, // 1
    0x00, 0x23, 0x67, 0x4D, 0x49, 0x79, 0x31, 0x00, // 2
    0x00, 0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00, // 3
    0x00, 0x0C, 0x1C, 0x32, 0x7F, 0x7F, 0x04, 0x00, // 4
    0x00, 0x72, 0x73, 0x51, 0x51, 0x5F, 0x4E, 0x00, // 5
    0x00, 0x1E, 0x3F, 0x69, 0x49, 0x4F, 0x06, 0x00, // 6
    0x00, 0x40, 0x47, 0x4F, 0x58, 0x70, 0x60, 0x00, // 7
    0x00, 0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, // 8
    0x00, 0x30, 0x79, 0x49, 0x4B, 0x7E, 0x3C, 0x00, // 9
};

static const __flash map level_1 = {
    .cols = 17,
    .rows = 9,
    .tiles = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
    }
};

void draw_block(const byte __memx *glyph, int x, int y);
void draw_map(const map __memx *m, word x, word y);
void draw_sprite(sprite *s);

byte check_collision(sprite *s, const __memx map *m);

#endif