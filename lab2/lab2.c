#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t tc = 0x00;
  if(timer_get_conf(timer,&tc)==0){
    timer_display_conf(timer,tc,field);
    return 0;
  }
  else{return 1;}
}


int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  timer_set_frequency(timer,freq);
  return 0;
}

int(timer_test_int)(uint8_t time) {
  uint8_t bit_no = 0;
  timer_subscribe_int(&bit_no);
  int count = 0;
  int ipc_status,r;
  int irq_set = 1;
  message msg;
  while( count/60 <time ) {
    if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            count+=1;
            if(count % 60==0)
              timer_print_elapsed_time();
          }
          break;
        default:
          break;
      }
    }
    else {}
  }
  timer_unsubscribe_int();
  return 0;
}
