#pragma once
#include <lcom/lcf.h>
#include "video_gr.h"
#include "sprites/apple.xpm"

typedef struct {
    int x;   
    int y;    
    xpm_image_t img;
} apple;

void (create_apple)();

void (draw_apple)();
