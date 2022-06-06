#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include "keyboard.h"
#include <stdbool.h>
#include <stdint.h>


extern uint8_t last;
extern uint32_t cnt;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  uint8_t bit_no=0;
  int ipc_status,r;
  int irq_set = 1;
  message msg;
  kbd_subscribe_int(&bit_no);
  while(last!=ESC) {
    tickdelay(micros_to_ticks(DELAY_US));
    if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
          }
          break;
        default:
          break;
      }
    }
    else {}
  }
  kbd_unsubscribe_int();
  kbd_print_no_sysinb(cnt);
  return 0;
}

int(kbd_test_poll)() {
  uint8_t status = 0;
  uint8_t scancode = 0;
  bool make = true;

  while(last!=ESC){

    make=true;
    tickdelay(micros_to_ticks(DELAY_US));

   if (util_sys_inb(STAT_REG,&status)){
     return 1;
   }
   if (status & ST_OUT_BUF){
     if (status &( ST_PAR_ERR | ST_TO_ERR | ST_MOUSE_DATA)){
       return 1;
     }
     if(util_sys_inb(OUT_BUF,&scancode)){
       return 1;
     }

     last = scancode;
     uint8_t bytes[2];
     bytes[0] = scancode;


     if(scancode == TWOBYTES){
      if(util_sys_inb(OUT_BUF,&scancode)){
         return 1;
       }
       if(scancode & BIT(7)){
         make = false;
       }
       bytes[1]=scancode;
       kbd_print_scancode(make,2,bytes);
     }
     else{
       if(scancode & BIT(7)){
         make = false;
       }
       kbd_print_scancode(make,1,bytes);
     }
   }
  }
  sys_outb(0x64,0x60);
  sys_outb(0x60, BIT(0)|BIT(1));
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {

  return 0;
}
