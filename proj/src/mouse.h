#pragma once
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "utils.h"
#include "i8042.h"
#include "video_gr.h"
#include "sprites/cursor.xpm"

typedef struct {
    int x, y;
    xpm_image_t img;
} Cursor;

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

void (buildPacket)(struct packet * pacote);

int(mouse_write_cmd)(uint32_t cmd, uint8_t *resp);

int (mouse_enable_data_report)();

int (mouse_disable_data_report)();

Cursor * (create_cursor)();

void (draw_cursor)();

void (clean_cursor)();

void (mouse_update)(struct packet * pacote);

unsigned int (check_collision_main_menu)();

