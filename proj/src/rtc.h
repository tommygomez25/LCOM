#pragma once
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "utils.h"
#include <math.h>

#define RTC_IRQ 8

#define RTC_ADDR_REG 0x70 //WRITE THE ADDRESS OF THE REGISTER TO RTC_ADDR_REG 
#define RTC_DATA_REG 0x71 //READ/WRITE ONE BYTE FROM/TO RTC_DATA_REG

#define RTC_SECONDS 0
#define RTC_MINUTES 2
#define RTC_HOURS 4
#define RTC_WEEK_DAY 6
#define RTC_DAY 7
#define RTC_MONTH 8
#define RTC_YEAR 9

#define RTC_A 10
#define RTC_UIP BIT(7)

#define RTC_B 11
#define RTC_SET BIT(7)
#define RTC_PIE BIT(6)
#define RTC_AIE BIT(5)
#define RTC_UIE BIT(4)
#define RTC_DM BIT(2)

#define RTC_C 12
#define RTC_PF BIT(6)
#define RTC_AF BIT(5)
#define RTC_UF BIT(4)

#define RTC_D 13

/**
 * @brief Subscribes rtc interrupts, defines the corresponding interrupt source (UIE) and sets the date/time register to be read in binary mode.
 * 
 * @param bit_no Variable that will store the RTC IRQ 
 * @return int 0 if success, 1 otherwise
 */
int rtc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes rtc interrupts 
 * 
 * @return int 0 if success, 1 otherwise
 */
int rtc_unsubscribe_int();

/**
 * @brief handles rtc interrupts
 * 
 */
void rtc_ih();

/**
 * @brief reads a register from the rtc
 * 
 * @param reg register to be read
 * @return int value that was read from the register ( 1 if no success)
 */
int rtc_read(uint8_t reg);

/**
 * @brief converts a number from binary to decimal
 * 
 * @param bcdNum binary number
 * @return uint8_t converted decimal number 
 */
uint8_t convert_from_binary (uint8_t bcdNum);

/**
 * @brief prints the actual date and time
 * 
 */
void print_clock();

/**
 * @brief sees if there is an update in progress on the rtc
 * 
 * @return int 0 if success, 1 otherwise
 */
int wait_regA_rtc();
