#include "apple.h"

apple* apple1;

void (create_apple)(){
    apple1 = malloc(sizeof(apple));
    apple1->x = 600;
    apple1->y = 500;
    apple1->xmap = apple_xpm;
}
