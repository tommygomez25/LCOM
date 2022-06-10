#include "menu.h"

extern uint8_t scancode;
extern unsigned int h_res, v_res;
extern int COUNTER;
extern uint8_t last;
extern int score;

struct packet pack;

extern Cursor *cursor;
extern GameState gameState;

void(loadMainMenu)() {
  xpm_load(menu_xpm, XPM_8_8_8, &menu_img);
  xpm_load(highlight_button_xpm, XPM_8_8_8, &highlight_button_img);
  xpm_load(logotip_xpm, XPM_8_8_8, &logotip_img);
  // xpm_load(menu_background_xpm,XPM_8_8_8,&menu_background_img);
  cursor = create_cursor();
  draw_main_menu_background();
  draw_cursor();
}

void(draw_main_menu_background)() {
  // draw_xpm(menu_background_img.bytes,&menu_background_img,0,0);
  draw_xpm(logotip_img.bytes, &logotip_img, 250, 50);
  draw_xpm(menu_img.bytes, &menu_img, 0, 0);
}

void MainMenuInterruptHandler(Device device) {
  static struct mouse_ev *mouseEvent;
  static bool overExit = false, overPlay = false, overScoreboard = false;
  bool clickedExit = false, clickedPlay = false, clickedScoreboard = false;

  switch (device) {
    case TIMER:
      if (COUNTER % 2 == 0) {
        switch (check_collision_main_menu()) {
          case 0: // cursor is not in any button
            if (overExit) {
              overExit = false;
              delete_xpm(highlight_button_img, 440, 435); // deletes the highlight for 'EXIT'
            }
            else if (overPlay) {
              overPlay = false;
              delete_xpm(highlight_button_img, 450, 205); // deletes the higtlight  for 'PLAY'
            }
            else if (overScoreboard) {
              overScoreboard = false;
              delete_xpm(highlight_button_img, 530, 320); // deletes the highlight for 'SCOREBOARD'
            }
            break;
          case 1: // cursor is over 'PLAY'
            if (mouseEvent->type == LB_RELEASED) {
              clickedPlay = true;
              break;
            }
            if (!overPlay) {
              overPlay = true;
            }
            break;
          case 2: // cursor is over 'SCOREBOARD'
            if (mouseEvent->type == LB_RELEASED) {
              clickedScoreboard = true;
              break;
            }
            if (!overScoreboard) {
              overScoreboard = true;
            }
            break;

          case 3: // cursor is over 'EXIT'
            if (mouseEvent->type == LB_RELEASED) {
              clickedExit = true;
              break;
            }
            if (!overExit) {
              overExit = true;
            }
            break;
        }

        clean_cursor();

        draw_main_menu_background();

        if (overPlay) {
          draw_xpm(highlight_button_img.bytes, &highlight_button_img, 450, 205);
        }
        else if (overScoreboard) {
          draw_xpm(highlight_button_img.bytes, &highlight_button_img, 530, 320);
        }
        else if (overExit) {
          draw_xpm(highlight_button_img.bytes, &highlight_button_img, 440, 435);
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
      print_clock();
      // clean_clock();
      // updateDateTime();
      // draw_clock();
      break;
  }

  if (clickedExit) { // Sair
    gameState = EXIT;
  }

  else if (clickedPlay) { // Entrar no modo PLAY
    gameState = PLAY;
    loadGame();
    printf("loaded game\n");
    return;
  }

  else if (clickedScoreboard) { // Entrar no Scoreboard
    gameState = SCOREBOARD;
    // draw_help_background();
    return;
  }
  // else
  // return;*/
}

void GameLostInterruptHandler(Device device) {

  switch (device) {
    case TIMER:
      break;
    case KEYBOARD:
      if (last == ESC) {
        gameState = MAINMENU;
        delete_xpm(yourScoreWas_img,206,300);
        delete_xpm(youLost_img,265,230);
        delete_xpm(black_background_img,0,0);
        score = 0;
        loadMainMenu();
      }
      break;
    case MOUSE:
      break;
    case RTC:
      break;
  }

}

void (loadLostMenu)(){
  xpm_load(black_background_xpm,XPM_8_8_8,&black_background_img);
  xpm_load(yourScoreWas_xpm,XPM_8_8_8,&yourScoreWas_img);
  xpm_load(youLost_xpm,XPM_8_8_8,&youLost_img);
  draw_xpm(black_background_img.bytes,&black_background_img,0,0);
  draw_xpm(youLost_img.bytes,&youLost_img,265,230);
  draw_xpm(yourScoreWas_img.bytes,&yourScoreWas_img,206,300);
  draw_score(585,305);
}
