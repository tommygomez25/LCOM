#include "snake.h"

snakepart* snake;

void (create_snake)(){
    snake = malloc(50 * sizeof *snake);

    for(int i = 0;i<50;i++){
        snake[i].xmap = (xpm_row_t*)malloc(sizeof(xpm_row_t*));
    }

    create_snake_tail();
    create_snake_body();
    create_snake_head();
}

void (create_snake_tail)(){
    snakepart tail;
    tail.x = 360;
    tail.y = 300;
    tail.xmap = snaketailright;
    snake[0] = tail;
}

void (create_snake_body)(){
    snakepart body;
    body.x = 380;
    body.y = 300;
    body.xmap = snakebodyhorizontal;
    snake[1] = body;
}


void (create_snake_head)(){
    snakepart head;
    head.x = 400;
    head.y = 300;
    head.xmap = snakeheadright;
    snake[2] = head;
}
