#include "snake.h"

snakepart *snake;
int size= 3;

void(create_snake)() {
  snake = malloc(50 * sizeof *snake);

  for (int i = 0; i < 50; i++) {
    snake[i].xmap = (xpm_row_t *) malloc(sizeof(xpm_row_t *));
  }

  create_snake_tail();
  create_snake_body();
  create_snake_head();
}

void(create_snake_tail)() {
  snakepart tail;
  tail.x = 360;
  tail.y = 300;
  tail.xmap = snaketailright;
  snake[0] = tail;
}

void(create_snake_body)() {
  snakepart body;
  body.x = 380;
  body.y = 300;
  body.xmap = snakebodyhorizontal;
  snake[1] = body;
}

void(create_snake_head)() {
  snakepart head;
  head.x = 400;
  head.y = 300;
  head.xmap = snakeheadright;
  snake[2] = head;
}

void(draw_snake)() {
  for (int i = 0; i < size; i++) {
    get_xpm(snake[i].xmap, snake[i].x, snake[i].y);

    /* if is body */
    if (i < size - 1) {
      snake[i].x = snake[i + 1].x;
      snake[i].y = snake[i + 1].y;
    }
  }
}

void(check_snake_apple_collision)(uint8_t last, apple *apple1) {

  if (snake[size - 1].x == apple1->x && snake[size - 1].y == apple1->y) {
    snake[size] = snake[size - 1];
    if (last == UP) {
      snake[size].y -= 20;
      snake[size - 1].xmap = snakebodyvertical;
    }
    else if (last == DOWN) {
      snake[size].y += 20;
      snake[size - 1].xmap = snakebodyvertical;
    }
    else if (last == LEFT) {
      snake[size].x -= 20;
      snake[size - 1].xmap = snakebodyhorizontal;
    }
    else {
      snake[size].x += 20;
      snake[size - 1].xmap = snakebodyhorizontal;
    }

    (size)++;
    apple1->x = (rand() % 40) * 20;
    apple1->y = ((rand() % 22) + 8) * 20;
  }
}