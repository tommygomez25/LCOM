#pragma once
#include <lcom/lcf.h>
#include "sprites/grass.xpm"
#include "video_gr.h"

/**
 * @brief A struct to save the position of the grass, as well as the xpm image that defines it
 * 
 */
typedef struct {
    int x;   
    int y;    
    xpm_image_t img;
} grass;

/**
 * @brief allocates memory for the background grass in the game board, loads the xpm of the grass and initializes the grass position
 * 
 */
void (create_grass)();

/**
 * @brief draws the grass in the game board
 * 
 */
void (draw_grass)();
