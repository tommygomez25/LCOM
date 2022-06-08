#pragma once
#include "video_gr.h"
#include "sprites/menu.xpm"
#include "game.h"   
#include "mouse.h"


void (loadMainMenu)();

void (draw_main_menu_background)();

void MainMenuInterruptHandler(Device device);


