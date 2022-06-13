#pragma once
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
  
#define VIDEO_CARD 0x10

/**
 * @brief sets the video graphic mode
 * 
 * @param mode video mode
 * @return void* 
 */
 void *vg_init(uint16_t mode);
  
  /**
   * @brief draws an horizontal line on the screen
   * 
   * @param x x coordenate of the left corner
   * @param y y coordenate of the left corner
   * @param len length of the line
   * @param color color of the line
   * @return int 0 if success, 1 otherwise
   */
 int vg_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
  
  /**
   * @brief draws a rectangle on the screen
   * 
   * @param x x of the left upper corner
   * @param y y of the left upper corner
   * @param width rectangle width
   * @param height rectangle height
   * @param color rectangle color
   * @return int 0 if success, 1 otheriwse
   */
 int vg_draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief draws a pixel on the screen
 * 
 * @param x x coordenate 
 * @param y y coordenate
 * @param color pixel color
 * @return int 0 if success, 1 otherwise
 */
int vg_draw_pixel (uint16_t x, uint16_t y, uint32_t color);
  
  /**
   * @brief Get the xpm object and draws it
   * 
   * @param xmap xmap to be loaded
   * @param x x coordenate to start drawing
   * @param y y coordenate to start drawing
   * @return int 0 if success, 1 otherwise
   */
int get_xpm(xpm_map_t xmap, uint16_t x, uint16_t y);

/**
 * @brief draws a xpm on the screen
 * 
 * @param map vram memory
 * @param img xpm img
 * @param x x coordenate
 * @param y y coordenate
 */
void draw_xpm(uint8_t *map, xpm_image_t * img, uint16_t x, uint16_t y);

/**
 * @brief deletes a xpm from the screen
 * 
 * @param img xpm img
 * @param x x coordenate
 * @param y y coordenate
 * @return int 0 if success, 1 otheriwse
 */
int delete_xpm(xpm_image_t img, uint16_t x, uint16_t y);

void swap_buffer();

/**
 * @brief implementation of double buffer, copy secondary memory to main memory
 * 
 */
void double_buffer();

