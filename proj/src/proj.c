
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "apple.h"
#include "grass.h"
#include "i8042.h"
#include "keyboard.h"
#include "snake.h"
#include "video_gr.h"
#include "menu.h"

extern uint8_t last;
extern uint32_t COUNTER;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern snakepart *snake;
extern apple *apple1;
extern int size;

int(proj_main_loop)() {
  vg_init(0x115);

  create_apple();
  create_snake();

  uint8_t previousmove = RIGHT;
  
  int ipc_status, r;
  int irq_tmr;
  int irq_kbd;

  uint8_t timer_bit_no, kbd_bit_no, mouse_bit_no;
  message msg;
  uint8_t gameover = 0;
  if (kbd_subscribe_int(&kbd_bit_no) != 0) {return 1;}
  if (timer_subscribe_int(&timer_bit_no) != 0) {return 1;}
  
  irq_kbd = BIT(kbd_bit_no);
  irq_tmr = BIT(timer_bit_no);

  loadMainMenu();

  while (last != ESC && gameover != 1) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_kbd) {
            kbc_ih();
          }
          if (msg.m_notify.interrupts & irq_tmr) {
            timer_int_handler();
            if ((COUNTER % 1) == 0) {
              check_snake_apple_collision(last, apple1);
              // vg_draw_rectangle(0, 0, 800, 150, 0x966F33);
              // draw_grass();
              // draw_apple();
              // draw_snake();
              if (snake[0].y == snake[1].y) {
                if (snake[0].x > snake[1].x) {
                  snake[0].xmap = snaketailleft;
                }
                else {
                  snake[0].xmap = snaketailright;
                }
              }
              else {
                if (snake[0].y > snake[1].y) {
                  snake[0].xmap = snaketailup;
                }
                else {
                  snake[0].xmap = snaketaildown;
                }
              }

              int speed = 20;

              if (last == UP && previousmove != DOWN) {
                snake[size - 1].xmap = snakeheadup;
                snake[size - 1].y -= speed;
                previousmove = UP;
              }
              else if (last == DOWN && previousmove != UP) {
                snake[size - 1].xmap = snakeheaddown;
                snake[size - 1].y += speed;
                previousmove = DOWN;
              }
              else if (last == RIGHT && previousmove != LEFT) {
                snake[size - 1].xmap = snakeheadright;
                snake[size - 1].x += speed;
                previousmove = RIGHT;
              }
              else if (last == LEFT && previousmove != RIGHT) {
                snake[size - 1].xmap = snakeheadleft;
                snake[size - 1].x -= speed;
                previousmove = LEFT;
              }
              else {
                if (previousmove == UP) {
                  snake[size - 1].xmap = snakeheadup;
                  snake[size - 1].y -= speed;
                  previousmove = UP;
                }
                else if (previousmove == DOWN) {
                  snake[size - 1].xmap = snakeheaddown;
                  snake[size - 1].y += speed;
                  previousmove = DOWN;
                }
                else if (previousmove == RIGHT) {
                  snake[size - 1].xmap = snakeheadright;
                  snake[size - 1].x += speed;
                  previousmove = RIGHT;
                }
                else if (previousmove == LEFT) {
                  snake[size - 1].xmap = snakeheadleft;
                  snake[size - 1].x -= speed;
                  previousmove = LEFT;
                }
              }
              for (int i = 1; i < size - 1; i++) {
                if ((snake[i - 1].x > snake[i].x && snake[i].x > snake[i + 1].x) || (snake[i - 1].x < snake[i].x && snake[i].x < snake[i + 1].x)) {
                  snake[i].xmap = snakebodyhorizontal;
                }
                else if ((snake[i - 1].y > snake[i].y && snake[i].y > snake[i + 1].y) || (snake[i - 1].y < snake[i].y && snake[i].y < snake[i + 1].y)) {
                  snake[i].xmap = snakebodyvertical;
                }
                else if ((snake[i - 1].y > snake[i].y && snake[i - 1].x == snake[i].x && snake[i + 1].y == snake[i].y && snake[i + 1].x > snake[i].x) || (snake[i + 1].y > snake[i].y && snake[i + 1].x == snake[i].x && snake[i - 1].y == snake[i].y && snake[i - 1].x > snake[i].x)) {
                  snake[i].xmap = snaketurnupleft;
                }
                else if ((snake[i - 1].y < snake[i].y && snake[i - 1].x == snake[i].x && snake[i + 1].y == snake[i].y && snake[i + 1].x < snake[i].x) || (snake[i + 1].y < snake[i].y && snake[i + 1].x == snake[i].x && snake[i - 1].y == snake[i].y && snake[i - 1].x < snake[i].x)) {
                  snake[i].xmap = snaketurndownright;
                }
                else if ((snake[i - 1].y > snake[i].y && snake[i - 1].x == snake[i].x && snake[i + 1].y == snake[i].y && snake[i + 1].x < snake[i].x) || (snake[i + 1].y > snake[i].y && snake[i + 1].x == snake[i].x && snake[i - 1].y == snake[i].y && snake[i - 1].x < snake[i].x)) {
                  snake[i].xmap = snaketurnupright;
                }
                else if ((snake[i - 1].y < snake[i].y && snake[i - 1].x == snake[i].x && snake[i + 1].y == snake[i].y && snake[i + 1].x > snake[i].x) || (snake[i + 1].y < snake[i].y && snake[i + 1].x == snake[i].x && snake[i - 1].y == snake[i].y && snake[i - 1].x > snake[i].x)) {
                  snake[i].xmap = snaketurndownleft;
                }
              }
              if (snake[size - 1].x > 800 || snake[size - 1].x < 0 || snake[size - 1].y < 150 || snake[size - 1].y > 600) {
                gameover = 1;
              }
              for (int i = 0; i < size - 2; i++) {
                if (snake[i].x == snake[size - 1].x && snake[i].y == snake[size - 1].y) {
                  //gameover = 1;
                  break;
                }
              }
              swap_buffer();
            }
            else {
            }
          }
          break;
        default:
          break;
      }
    }
    else {
    }
  }
  free(snake);
  free(apple1);
  timer_unsubscribe_int();
  kbd_unsubscribe_int();
  vg_exit();
  return 1;
}
