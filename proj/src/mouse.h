#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "utils.h"
#include "i8042.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

void (buildPacket)(struct packet * pacote);

int(mouse_write_cmd)(uint32_t cmd, uint8_t *resp);

int (mouse_disable_data_reporting)();
