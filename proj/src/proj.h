#pragma once

typedef enum {TIMER, KEYBOARD, MOUSE, RTC} Device;

typedef enum {MAINMENU,PLAY, LOST, WON, PAUSEMENU, HELP, EXIT} GameState;

void GeneralInterrupt(Device device);
