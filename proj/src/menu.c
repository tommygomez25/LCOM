#include "menu.h"

extern uint8_t scancode;
extern unsigned int h_res, v_res;

struct packet pack;

extern Cursor * cursor;
extern GameState gameState;

void (loadMainMenu)(){
  get_xpm(menu_xpm,0,0);
  cursor = create_cursor();
  draw_cursor();
}

void (draw_main_menu_background)(){
  get_xpm(menu_xpm,0,0);
}

void MainMenuInterruptHandler(Device device) {
  static struct mouse_ev * mouseEvent;
  static bool overExit = false, overPlay = false,overScoreboard = false;
  bool clickedExit = false, clickedPlay = false, clickedScoreboard = false;

  switch (device) {
    case TIMER:
      switch(check_collision_main_menu()) {
        case 0: // cursor is not in any button
          if (overExit) {
            overExit = false;
          }
          else if (overPlay) {
            overPlay = false;
          }
          else if (overScoreboard) {
            overScoreboard = false;
          }
          break;
        case 1: // cursor is over 'PLAY'
          if (mouseEvent->type == LB_RELEASED) {
            clickedPlay = true;
            break;
          }
          if (!overPlay) {
            overPlay = true;
            draw_main_menu_background();
            /*
            mainMenuButtons[3]->mouseOver = true;
            add_button_to_background(mainMenuButtons[3]);
            draw_button(mainMenuButtons[3]);*/
          }
          break;
        case 2: // cursor is over 'SCOREBOARD'
          if (mouseEvent->type == LB_RELEASED) {
            clickedScoreboard = true;
            break;
          }
          if (!overScoreboard) {
            overScoreboard = true;
            draw_main_menu_background();
            /*
            mainMenuButtons[0]->mouseOver = true;
            add_button_to_background(mainMenuButtons[0]);
            draw_button(mainMenuButtons[0]);*/
          }
          break;
        case 3: // cursor is over 'EXIT'
          if (mouseEvent->type == LB_RELEASED) {
            clickedExit = true;
            break;
          }
          if (!overExit) {
            overExit = true;
            draw_main_menu_background();
            /*
            mainMenuButtons[1]->mouseOver = true;
            add_button_to_background(mainMenuButtons[1]);
            draw_button(mainMenuButtons[1]);*/
          }
          break;
      }
      break;
    case KEYBOARD: 
      break;
    case MOUSE:
      mouseEvent = mouse_events(&pack);
      mouse_update(&pack);
      break;
    case RTC:
      //print_clock();
      //clean_clock();
      //updateDateTime();
      //draw_clock();
      break;
  }
  
  if (clickedExit) // Sair
    gameState = EXIT;
  /*
  else if (clickedPlay) { // Entrar no modo PLAY
    gameState = PLAY;
    //clean_clock();
    //LoadSinglePLayer(1,true);
  }
  else if (clickedScoreboard) { // Entrar no Scoreboard
    gameState = SCOREBOARD;
    //draw_help_background();
    return;
  }
  //else
    //return;*/
}

