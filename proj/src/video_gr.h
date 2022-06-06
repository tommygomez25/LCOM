#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
  
<<<<<<< HEAD
#define VIDEO_CARD 0x10

=======
>>>>>>> 497ceeb0ebfbf98e50ffa0edcc2d5b9d906975d3
 void *(vg_init)(uint16_t mode);
  
 int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
  
 int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
  
 int (vg_exit)(void);
  int (vg_draw_pixel) (uint16_t x, uint16_t y, uint32_t color);
  
int get_xpm(xpm_map_t xmap, uint16_t x, uint16_t y);

void draw_xpm(uint8_t *map, xpm_image_t * img, uint16_t x, uint16_t y);


int delete_xpm(xpm_map_t xmap, uint16_t x, uint16_t y);

<<<<<<< HEAD
void (swap_buffer)();
=======
int swap_buffer();
>>>>>>> 497ceeb0ebfbf98e50ffa0edcc2d5b9d906975d3

