#pragma once
#include <lcom/lcf.h>
#include "video_gr.h"
#include "sprites/apple.xpm"

/**
 * @brief Struct relative to apple
 * 
 */
typedef struct {
    int x;   
    int y;    
    xpm_image_t img;
    int counter;
} apple;

/**
 * @brief allocates memory for an apple, loads the xpm of the apple and initializes the apple position
 * 
 */

void create_apple();

/**
 * @brief draws the apple in the game board
 * 
 */

void draw_apple();

/**
 * @brief generates x and y coordenates for the apple
 * 
 */
void move_apple();
