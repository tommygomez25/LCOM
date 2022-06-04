#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
  
 void *(vg_init)(uint16_t mode);
  
 int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
  
 int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
  
 int (vg_exit)(void);
  int (vg_draw_pixel) (uint16_t x, uint16_t y, uint32_t color);
  
int get_xpm(xpm_map_t xmap, uint16_t x, uint16_t y);

void draw_xpm(uint8_t *map, xpm_image_t * img, uint16_t x, uint16_t y);

int video_move_onePixeldisplacement(xpm_map_t xpm,uint16_t *x, uint16_t *y, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate);

int video_move_consecutiveFramesDisplacement(xpm_map_t xpm, uint16_t *x, uint16_t *y, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,int16_t speed, uint8_t fr_rate);

int delete_xpm(xpm_map_t xmap, uint16_t x, uint16_t y);

int get_current_buffer(reg86_t *r);
int swap_buffer();

