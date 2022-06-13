#pragma once

#include "i8042.h"
#include "keyboard.h"
#include "timer.h"
#include "rtc.h"

typedef enum {TIMER, KEYBOARD, MOUSE, RTC} Device;

typedef enum {MAINMENU,PLAY, LOST, SAVE, SCOREBOARD, EXIT} GameState;

#include "snake.h"
#include "menu.h"
#include "grass.h"
#include "sprites/0.xpm"
#include "sprites/1.xpm"
#include "sprites/2.xpm"
#include "sprites/3.xpm"
#include "sprites/4.xpm"
#include "sprites/5.xpm"
#include "sprites/6.xpm"
#include "sprites/7.xpm"
#include "sprites/8.xpm"
#include "sprites/9.xpm"

xpm_image_t numbers_img[10];

/**
 * @brief This function is where the main loop occur. First, all the device interrupts are subscribed , then there is a loop to see what device generated the interrupt.
 * @return 1 if an error occured, 0 otherwise
 */

int game_main_loop();

/**
 * @brief This function receives a device interrupt and depending on the game state of the game, calls the right function to handle the interrupt.
 * 
 * @param device Device that generated the interrupt.
 */

void GeneralInterrupt(Device device);

/**
 * @brief checks the mouse packet received in the argument, in order to return what event occured in the mouse
 * 
 * @param pack pack of the mouse
 * @return struct mouse_ev* Type of the event occured in the mouse
 */

struct mouse_ev * mouse_events(struct packet * pack);

/**
 * @brief Handles the interrupt received from the device , during gamestate  'PLAY'
 * 
 * @param device Device that generated the interrupt
 */

void PlayInterruptHandler(Device device);

/**
 * @brief Loads the XPMs needed for the gameState 'PLAY'
 * 
 */

void loadGame();

/**
 * @brief Draws the current score in the board of the game
 * 
 */

void draw_score();
