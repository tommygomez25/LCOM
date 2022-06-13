#pragma once
#include <lcom/lcf.h>
#include "sprites/grass.xpm"
#include "video_gr.h"

typedef struct {
    int x;   
    int y;    
    xpm_image_t img;
} grass;

/**
 * @brief allocates memory for the background grass in the game board, loads the xpm of the grass and initializes the grass position
 * 
 */

void create_grass();

/**
 * @brief draws the grass in the game board
 * 
 */

void draw_grass();
