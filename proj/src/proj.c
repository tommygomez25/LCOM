#include <lcom/lcf.h>
#include "video_gr.h"
#include "i8042.h"
#include "keyboard.h"
#include "xpm.h"
#include <stdint.h>
#include <stdio.h>

extern uint8_t last;
extern uint32_t COUNTER;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)() {
  vg_init(0x115);
  vg_draw_rectangle(0,0,800,150,0x966F33);
  
  int xtail = 360;
  int ytail = 300;
  int xbody = 380;
  int ybody = 300;
  int xhead = 400;
  int yhead = 300;
  uint8_t bit_no=0;
  int ipc_status,r;
  int irq_tmr;
  int irq_kbd;
  static xpm_row_t const* body = snakebodyhorizontal;
 static xpm_row_t const* head = snakeheadright;
 static xpm_row_t const* tail = snaketailright;
  message msg;
  if(kbd_subscribe_int(&bit_no) != 0)
      return 1; 
  irq_kbd = BIT(bit_no);
  
  if(timer_subscribe_int(&bit_no) != 0)
    return 1;
  irq_tmr = BIT(bit_no);
  while(last!=ESC) {
    if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_kbd) {
            kbc_ih();
          }
          if(msg.m_notify.interrupts & irq_tmr){
            timer_int_handler();
               if((COUNTER % 1)==0){
                    get_xpm(grass,0,150);
                    get_xpm(tail,  xtail,  ytail);
                    get_xpm(body,  xbody,  ybody);
                    get_xpm(head,  xhead,  yhead);
                    int x = 20;
                    
                     xtail=xbody;
                     ytail=ybody;
                     xbody=xhead;
                     ybody=yhead;
                     if(ytail==ybody){
                      if(xtail>xbody){
                        tail=snaketailleft;
                      }
                      else{
                        tail=snaketailright;
                      }
                     
                    }
                    else{
                      if(ytail>ybody){
                        tail=snaketailup;
                      }
                      else{
                        tail=snaketaildown;
                      }
                      
                    }  
                    if(last==UP){
                      head=snakeheadup;
                      yhead-=x;
                    }  
                    else if(last==DOWN){
                      head=snakeheaddown;
                      yhead+=x;

                    }
                    else if(last==RIGHT){
                      head=snakeheadright;
                      xhead+=x;
                      
                    }
                    else if(last==LEFT){
                      head=snakeheadleft;
                      xhead-=x;
                    }  
                    if((xtail>xbody && xbody>xhead) || (xtail<xbody && xbody<xhead)){
                      body = snakebodyhorizontal;
                    }
                    else if((ytail>ybody && ybody>yhead) || (ytail<ybody && ybody<yhead)){
                      body = snakebodyvertical;
                    }
                    else if((ytail>ybody && xtail == xbody && yhead==ybody && xhead > xbody)|| (yhead>ybody && xhead == xbody && ytail==ybody && xtail > xbody)){
                      body = snaketurnupleft;
                    }
                    else if((ytail<ybody && xtail == xbody && yhead==ybody && xhead < xbody)|| (yhead<ybody && xhead == xbody && ytail==ybody && xtail < xbody)){
                      body = snaketurndownright;
                    }
                    else if((ytail>ybody && xtail == xbody && yhead==ybody && xhead < xbody)|| (yhead>ybody && xhead == xbody && ytail==ybody && xtail < xbody)){
                      body = snaketurnupright;
                    }
                    else if((ytail<ybody && xtail == xbody && yhead==ybody && xhead > xbody)|| (yhead<ybody && xhead == xbody && ytail==ybody && xtail > xbody)){
                      body = snaketurndownleft;
                    }
                    swap_buffer();
                }
              else{ }

          }
          break;
        default:
          break;
      }
    }
    else {}
  }
  timer_unsubscribe_int();
  kbd_unsubscribe_int();
  vg_exit();
  return 1;
}
