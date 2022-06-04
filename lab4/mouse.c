#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"

int hook_id = 0;

int (m_subscribe_int)(){
  sys_irqsetpolicy(12,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id);
  return 0;
}

int (m_unsubscribe_int)(){
  sys_irqrmpolicy(&hook_id);
  return 0;
}

void (mouse_ih)(){
  uint8_t status = 0;
  uint8_t scancode = 0;
  if (util_sys_inb(STAT_REG,&status)){
    return;
  }
  if (status & ST_OUT_BUF){
    if (status &( ST_PAR_ERR | ST_TO_ERR)){
      return;
    }

    if(util_sys_inb(OUT_BUF,&scancode)){
      return;
    }
  }
}
