#pragma once

#include "i8042.h"
#include "keyboard.h"
#include "timer.h"

typedef enum {TIMER, KEYBOARD, MOUSE, RTC} Device;

typedef enum {MAINMENU,PLAY, LOST, WON, PAUSEMENU, SCOREBOARD, EXIT} GameState;

#include "snake.h"
#include "menu.h"


int (game_main_loop)();

void GeneralInterrupt(Device device);

struct mouse_ev * mouse_events(struct packet * pack);
