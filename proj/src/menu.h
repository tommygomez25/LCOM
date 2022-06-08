#pragma once
#include "video_gr.h"
#include "sprites/menu.xpm"
#include "game.h"   
#include "mouse.h"

xpm_image_t background_menu;

void (loadMainMenu)();

void (draw_main_menu_background)();

void MainMenuInterruptHandler(Device device);


