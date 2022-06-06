#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include "utils.h"


#include "i8042.h"

int (kbd_subscribe_int)(uint8_t *bit_no);

int (kbd_unsubscribe_int)();

void (kbc_ih)();
