#ifndef MAIN_H
# define MAIN_H

#include "SPIKE.h"

typedef struct map {
    word cols;
    word rows;
    byte tiles[];
} map;

typedef struct sprite {
    word x;
    word y;
    word frame;
    
    word frame_duration;
    byte animation_length;
    word animation_timer;
    word frames[];
} sprite;

static const __flash byte GLYPHS[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x7f, 0xaf, 0xdf, 0xaf, 0xdf, 0xaf, 0xdf, 0x7f, 
    0x00, 0x00, 0x80, 0x76, 0xf6, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0xf6, 0x76, 0xa0, 0x00, 0x00, 
    0x00, 0x00, 0x38, 0x74, 0x7c, 0x7c, 0x38, 0x00, 
    0x00, 0x00, 0x00, 0x38, 0x7c, 0x38, 0x00, 0x00, 
};

static const __flash map level_1 = {
    .cols = 16,
    .rows = 8,
    .tiles = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    }
};


void draw_map(const map __memx *map, word x, word y);
void draw_sprite(sprite *s);

#endif