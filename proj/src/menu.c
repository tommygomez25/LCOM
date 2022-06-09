#include "menu.h"

extern uint8_t scancode;
extern unsigned int h_res, v_res;
extern int COUNTER;

struct packet pack;

extern Cursor * cursor;
extern GameState gameState;

void (loadMainMenu)(){
  xpm_load(menu_xpm,XPM_8_8_8,&menu_img);
  xpm_load(highlight_button_xpm,XPM_8_8_8,&highlight_button_img);
  xpm_load(menu_background_xpm,XPM_8_8_8,&menu_background_img);
  cursor = create_cursor();
  draw_main_menu_background();
  draw_cursor();
}

void (draw_main_menu_background)(){
  draw_xpm(menu_background_img.bytes,&menu_background_img,0,0);
  draw_xpm(menu_img.bytes,&menu_img,0,0);
}

void MainMenuInterruptHandler(Device device) {
  static struct mouse_ev * mouseEvent;
  static bool overExit = false, overPlay = false,overScoreboard = false;
  bool clickedExit = false, clickedPlay = false, clickedScoreboard = false;

  switch (device) {
    case TIMER:
    if(COUNTER % 3 == 0){
      switch(check_collision_main_menu()) {
        case 0: // cursor is not in any button
          if (overExit) {
            overExit = false;
            delete_xpm(highlight_button_img,440,435);
          }
          else if (overPlay) {
            overPlay = false;
            delete_xpm(highlight_button_img,470,200);
          }
          else if (overScoreboard) {
            overScoreboard = false;
            delete_xpm(highlight_button_img,530,325);
          }
          break;
        case 1: // cursor is over 'PLAY'
          if (mouseEvent->type == LB_RELEASED) {
            clickedPlay = true;
            break;
          }
          if (!overPlay) {
            overPlay = true;
            //draw_main_menu_background();
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
            //draw_main_menu_background();
            /*
            mainMenuButtons[1]->mouseOver = true;
            add_button_to_background(mainMenuButtons[1]);
            draw_button(mainMenuButtons[1]);*/
          }
          break;
      }
      
        clean_cursor();
        
        draw_main_menu_background();
        
        if(overPlay){
          draw_xpm(highlight_button_img.bytes,&highlight_button_img,450,205);
        }
        else if(overScoreboard){
          draw_xpm(highlight_button_img.bytes,&highlight_button_img,530,320);
        }
        else if(overExit){
          draw_xpm(highlight_button_img.bytes,&highlight_button_img,440,435);
        }
        draw_cursor();
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
  
  if (clickedExit) {// Sair
    gameState = EXIT;}
  
  else if (clickedPlay) { // Entrar no modo PLAY
    gameState = PLAY;
    loadGame();
    printf("loaded game\n");
    return ;
  }
  
  else if (clickedScoreboard) { // Entrar no Scoreboard
    gameState = SCOREBOARD;
    //draw_help_background();
    return;
  }
  //else
    //return;*/
}

