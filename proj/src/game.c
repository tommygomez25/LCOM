#include "game.h"

extern uint8_t last;     /* keyboard */
extern uint32_t COUNTER; /* timer */
extern uint8_t scancode; /* mouse */

struct packet pack;
struct mouse_ev mouse_event;

GameState gameState = MAINMENU;

extern Cursor *cursor;
extern snakepart *snake;
extern apple *apple1;
extern int size; /* snake size */

int(game_main_loop)() {

  //create_apple();
  //create_snake();

  // uint8_t previousmove = RIGHT;

  int ipc_status, r;
  message msg;

  uint8_t timer_bit_no, kbd_bit_no, mouse_bit_no;

  if (kbd_subscribe_int(&kbd_bit_no) != 0) {
    return 1;
  }
  if (timer_subscribe_int(&timer_bit_no) != 0) {
    return 1;
  }
  if (mouse_enable_data_report() != 0) {
    return 1;
  }
  if (mouse_subscribe_int(&mouse_bit_no) != 0) {
    return 1;
  }

  int irq_kbd = BIT(kbd_bit_no);
  int irq_tmr = BIT(timer_bit_no);
  int irq_mouse = BIT(mouse_bit_no);

  //uint8_t gameover = 0;
  bool MouseReadSecond = false, MouseReadThird = false;
  uint8_t ms_bytes[3]; /* to store mouse bytes */

  loadMainMenu();
  
  while (gameState != EXIT) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_kbd) {
            kbc_ih();
            GeneralInterrupt(KEYBOARD);
          }
          if (msg.m_notify.interrupts & irq_mouse) {
            mouse_ih();
            if (!MouseReadSecond && !MouseReadThird && (scancode & BIT(3))) {
              ms_bytes[0] = scancode;
              MouseReadSecond = true;
            }
            else if (MouseReadSecond) {
              ms_bytes[1] = scancode;
              MouseReadThird = true;
              MouseReadSecond = false;
            }
            else if (MouseReadThird) {
              ms_bytes[2] = scancode;
              MouseReadThird = false;
              for (unsigned int i = 0; i < 3; i++) {
                pack.bytes[i] = ms_bytes[i];
              }
              buildPacket(&pack);
              GeneralInterrupt(MOUSE);
            }
          }
          if (msg.m_notify.interrupts & irq_tmr) {
            timer_int_handler();
            GeneralInterrupt(TIMER);
            //swap_buffer();
            double_buffer();
          }
          break;
        default:
          break;
      }
    }
  }

  //free(snake);
  //free(apple1);
  if (timer_unsubscribe_int() != 0) {
    return 1;
  }
  if (kbd_unsubscribe_int() != 0) {
    return 1;
  }
  if (mouse_unsubscribe_int() != 0) {
    return 1;
  }
  if (mouse_disable_data_report() != 0) {
    return 1;
  }
  
  if (vg_exit()) {return 1;}
  
  return 1;
}

void GeneralInterrupt(Device device) {
  switch (gameState) {
    case MAINMENU:
      MainMenuInterruptHandler(device);
      break;
    case PAUSEMENU:
      // PauseMenuInterruptHandler(device);
      break;
    case PLAY:
      // PlayInterruptHandler(device);
      break;
    case SCOREBOARD:
      // HelpMenuInterruptHandler(device);
      break;
    case WON:
      // GameWonInterruptHandler(device);
      break;
    case LOST:
      // GameLostInterruptHandler(device);
      break;
    case EXIT:
      break;
  }
}

struct mouse_ev *mouse_events(struct packet *pack) {
  static bool lb_pressed = false, rb_pressed = false, mb_pressed = false;

  mouse_event.delta_x = pack->delta_x;
  mouse_event.delta_y = pack->delta_y;

  if (!lb_pressed && pack->lb && !rb_pressed && !mb_pressed && !pack->mb && !pack->rb) {
    lb_pressed = true;
    mouse_event.type = LB_PRESSED;
  }
  else if (!rb_pressed && pack->rb && !lb_pressed && !mb_pressed && !pack->mb && !pack->lb) {
    rb_pressed = true;
    mouse_event.type = RB_PRESSED;
  }
  else if (lb_pressed && !pack->lb && !rb_pressed && !mb_pressed && !pack->mb && !pack->rb) {
    lb_pressed = false;
    mouse_event.type = LB_RELEASED;
  }
  else if (rb_pressed && !pack->rb && !lb_pressed && !mb_pressed && !pack->mb && !pack->lb) {
    rb_pressed = false;
    mouse_event.type = RB_RELEASED;
  }
  else if (!mb_pressed && pack->mb) {
    mb_pressed = true;
    mouse_event.type = BUTTON_EV;
  }
  else if (mb_pressed && !pack->mb) {
    mb_pressed = false;
    mouse_event.type = BUTTON_EV;
  }
  else
    mouse_event.type = MOUSE_MOV;

  return &mouse_event;
}
