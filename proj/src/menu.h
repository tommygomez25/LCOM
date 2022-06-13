#pragma once
#include "video_gr.h"
#include "sprites/menu.xpm"
#include "sprites/highlight_button.xpm"
#include "sprites/menu_background.xpm"
#include "sprites/logotip.xpm"
#include "sprites/youLost.xpm"
#include "sprites/yourScoreWas.xpm"
#include "sprites/black_background.xpm"
#include "game.h"   
#include "mouse.h"

xpm_image_t menu_img;
xpm_image_t menu_background_img;
xpm_image_t highlight_button_img;
xpm_image_t logotip_img;
xpm_image_t youLost_img;
xpm_image_t yourScoreWas_img;
xpm_image_t black_background_img;

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

/**
 * @brief loads the screen of the state 'GAME LOST'
 * 
 */
void loadLostMenu();

