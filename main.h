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
    
    0x00, 0x7c, 0xfe, 0xb2, 0x9a, 0xfe, 0x7c, 0x00, // 0
    0x00, 0x08, 0x0c, 0xfe, 0xfe, 0x00, 0x00, 0x00, // 1
    0x00, 0x84, 0xc6, 0xe2, 0xb2, 0x9e, 0x8c, 0x00, // 2
    0x00, 0x44, 0xc6, 0x82, 0x92, 0xfe, 0x6c, 0x00, // 3
    0x30, 0x38, 0x2c, 0x26, 0xfe, 0xfe, 0x20, 0x00, // 4
    0x00, 0x4e, 0xce, 0x8a, 0x8a, 0xfa, 0x72, 0x00, // 5
    0x00, 0x78, 0xfc, 0x96, 0x92, 0xf2, 0x60, 0x00, // 6
    0x00, 0x00, 0x02, 0xe2, 0xf2, 0x1e, 0x0e, 0x00, // 7
    0x00, 0x6c, 0xfe, 0x92, 0x92, 0xfe, 0x6c, 0x00, // 8
    0x00, 0x0c, 0x9e, 0x92, 0xd2, 0x7e, 0x3c, 0x00, // 9
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