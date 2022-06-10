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

void (loadMainMenu)();

void (draw_main_menu_background)();

void MainMenuInterruptHandler(Device device);

void GameLostInterruptHandler(Device device);

void (loadLostMenu)();

