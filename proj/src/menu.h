#pragma once
#include "video_gr.h"
#include "sprites/menu.xpm"
#include "sprites/highlight_button.xpm"
#include "sprites/menu_background.xpm"
#include "game.h"   
#include "mouse.h"

xpm_image_t menu_img;
xpm_image_t menu_background_img;
xpm_image_t highlight_button_img;

void (loadMainMenu)();

void (draw_main_menu_background)();

void MainMenuInterruptHandler(Device device);


