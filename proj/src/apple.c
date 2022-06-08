#include "apple.h"

apple* apple1;

void (create_apple)(){
    apple1 = malloc(sizeof(apple));
    apple1->x = 600;
    apple1->y = 500;
    xpm_load(apple_xpm,XPM_8_8_8,&apple1->img);
}


void (draw_apple)(){
    draw_xpm(apple1->img.bytes,&apple1->img,apple1->x,apple1->y);
}
