#pragma once
#include <lcom/lcf.h>
#include "utils.h"


#include "i8042.h"

/**
 * @brief subscribes keyboard interrupts
 * 
 * @param bit_no variable that stores the IRQ value of the keyboard
 * @return int 0 if success, 1 otherwise
 */
int kbd_subscribe_int(uint8_t *bit_no);

/**
 * @brief unsubscribes keyboard interrupts
 * 
 */
int kbd_unsubscribe_int();

/**
 * @brief Controols Keyboard interrupts
 * 
 */
void kbc_ih();
