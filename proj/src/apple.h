#pragma once
#include <lcom/lcf.h>
#include "sprites/apple.xpm"

typedef struct {
    int x;   
    int y;    
    xpm_row_t* xmap;
} apple;

void (create_apple)();
