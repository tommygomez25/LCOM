#pragma once
#include "video_gr.h"
#include "sprites/menu.xpm"
#include "sprites/highlight_button.xpm"
#include "sprites/menu_background.xpm"
#include "sprites/logotip.xpm"
#include "sprites/youLost.xpm"
#include "sprites/yourScoreWas.xpm"
#include "sprites/black_background.xpm"
#include "sprites/writename.xpm"
#include "sprites/scoreboard.xpm"
#include "game.h"  
#include "alphabet.h"   
#include "mouse.h"

xpm_image_t menu_img;
xpm_image_t menu_background_img;
xpm_image_t highlight_button_img;
xpm_image_t logotip_img;
xpm_image_t youLost_img;
xpm_image_t yourScoreWas_img;
xpm_image_t black_background_img;
xpm_image_t scoreboard_img;
xpm_image_t name;
xpm_image_t a;
xpm_image_t b;
xpm_image_t c;
xpm_image_t d;
xpm_image_t e;
xpm_image_t f;
xpm_image_t g;
xpm_image_t h;
xpm_image_t i;
xpm_image_t j;
xpm_image_t k;
xpm_image_t l;
xpm_image_t m;
xpm_image_t n;
xpm_image_t o;
xpm_image_t p;
xpm_image_t q;
xpm_image_t r;
xpm_image_t s;
xpm_image_t t;
xpm_image_t u;
xpm_image_t v;
xpm_image_t w;
xpm_image_t x;
xpm_image_t y;
xpm_image_t z;

/**
 * @brief loads the XPMs of the menus (including mouse cursor) and draws the menu and the mouse cursor
 * 
 */
void loadMainMenu();

/**
 * @brief draws the menu
 * 
 */
void draw_main_menu_background();

/**
 * @brief This function handles an interrupt received from a device. Updates the cursor position, draws the updated image and checks if the mouse cursor collided with a button.
 * Changes the game state depending on the button clicked.
 * 
 * @param device Device that generated the interrupt
 */
void MainMenuInterruptHandler(Device device);

/**
 * @brief handles interrupt received mainly from keyboard when the game is lost ( if ESC is pressed, return to main menu)
 * 
 * @param device 
 */
void GameLostInterruptHandler(Device device);

void ScoreBoardInterruptHandler(Device device);

void SaveInterruptHandler(Device device) ;

/**
 * @brief loads the screen of the state 'GAME'
 * 
 */
void loadLostMenu();

/**
 * @brief load the screen of the state 'SAVE'
 * 
 */
void loadSaveMenu();

/**
 * @brief 
 * 
 * @param score 
 * @param name 
 */
void savescore(int score, char* name);

/**
 * @brief loads all the XPMs related to letters. Reads the highscores.txt file and draws on the screen the data that was read from the file (scoreboard)
 * 
 */
void draw_scoreboard();

/**
 * @brief draws a number on the screen
 * 
 * @param number array of digits ( this are the digits of the number)
 * @param liney y coordenate to draw the number
 */
void draw_number(char *number,int liney);

/**
 * @brief draws a name on the screen
 * 
 * @param name array of letters (this are the letters of the name)
 * @param liney y coordenate to draw the name
 */
void draw_name(char *name,int liney);

/**
 * @brief while the user is entering a letter (to enter his name), this function draws the xpm corresponding to that letter.
 * 
 * @param lastletter letter that was entered
 */
void letterhandle(uint8_t lastletter);
