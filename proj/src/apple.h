#pragma once
#include <lcom/lcf.h>
#include "video_gr.h"
#include "sprites/apple.xpm"

/**
 * @brief A struct to save the position of the apple, as well as the xpm image that defines it
 * 
 */
typedef struct {
    int x;   
    int y;    
    xpm_image_t img;
} apple;

/**
 * @brief allocates memory for an apple, loads the xpm of the apple and initializes the apple position
 * 
 */
void (create_apple)();

/**
 * @brief draws the apple in the game board
 * 
 */
void (draw_apple)();
