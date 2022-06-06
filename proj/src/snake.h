#pragma once
#include <lcom/lcf.h>
#include "sprites/snakebodyhorizontal.xpm"
#include "sprites/snakebodyvertical.xpm"
#include "sprites/snakeheaddown.xpm"
#include "sprites/snakeheadleft.xpm"
#include "sprites/snakeheadright.xpm"
#include "sprites/snakeheadup.xpm"
#include "sprites/snaketaildown.xpm"
#include "sprites/snaketailleft.xpm"
#include "sprites/snaketailright.xpm"
#include "sprites/snaketailup.xpm"
#include "sprites/snaketurndownleft.xpm"
#include "sprites/snaketurndownright.xpm"
#include "sprites/snaketurnupleft.xpm"
#include "sprites/snaketurnupright.xpm"
#include "i8042.h"
#include "apple.h"

typedef struct {
    int x;   
    int y;    
    xpm_row_t *xmap; /* snake é estruturado por xmp rows */
} snakepart;

void (create_snake)();

void (create_snake_tail)();

void (create_snake_body)();

void (create_snake_head)();

void (draw_snake)();

void (check_snake_apple_collision)(uint8_t last,apple* apple1);



