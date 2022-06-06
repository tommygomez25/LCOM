#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static char *video_mem_sec;
static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
extern uint32_t COUNTER;

void *(vg_init)(uint16_t mode){
  vbe_mode_info_t vmi;
  vbe_get_mode_info(mode, &vmi);
  h_res = vmi.XResolution;
  v_res = vmi.YResolution;
  bits_per_pixel = vmi.BitsPerPixel;

  struct minix_mem_range mr, mr_secondary;

  unsigned int vram_base = vmi.PhysBasePtr;
  unsigned int vram_size = h_res * v_res * (bits_per_pixel+7/8);
  
  unsigned int vram_base_secondary_buffer = vmi.PhysBasePtr + vram_size;
  int r;
  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size *2;
  mr_secondary.mr_base = (phys_bytes) vram_base_secondary_buffer;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);


  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
  video_mem_sec = vm_map_phys(SELF, (void *) mr_secondary.mr_base, vram_size);
  if(video_mem == MAP_FAILED ||video_mem_sec == MAP_FAILED )
    panic("couldn't map video memory");
  memset(video_mem, 0, vram_size);
  memset(video_mem_sec, 0, vram_size);
  reg86_t r86;
  memset(&r86, 0, sizeof(r86));
  r86.intno = 0x10;
  r86.ah = 0x4F;
  r86.al = 0x02;
  r86.bx = 1<<14|mode;
  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return NULL;
  }
  return 0;
}

int (vg_draw_pixel) (uint16_t x, uint16_t y, uint32_t color){
    uint32_t temp;
    char *pix_ad =  video_mem_sec + x * ((bits_per_pixel+7)/8) + (y * h_res *((bits_per_pixel+7)/8));
      temp = color;
      memcpy(pix_ad,&temp,(bits_per_pixel+7)/8);
    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for(int i = x;i<x+len;i++){
        vg_draw_pixel(i,y,color);
  }
  return 0;
}
  
 int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
     for(int i = y;i<y+height;i++){
       vg_draw_hline(x,i,width,color);
     }
     return 0;
 }

void draw_xpm(uint8_t *map, xpm_image_t * img, uint16_t x, uint16_t y){
   for(unsigned int i=0; i<img->height; i++){
    for(unsigned int j= 0; j<img->width; j++){
      uint32_t color = 0;
      for (size_t byte = 0; byte < (bits_per_pixel+7)/8; byte++) {
        color |= *(map + (j + i * img->width) * ((bits_per_pixel+7)/8) + byte) << (byte * 8);
      }
      if(color!=xpm_transparency_color(img->type))
       vg_draw_pixel(x + j, y + i, color);
    }
  }
}
int get_xpm(xpm_map_t xmap, uint16_t x, uint16_t y){
  uint8_t *map;
  xpm_image_t img;
  map = xpm_load(xmap,XPM_8_8_8,&img);
  if(map == NULL) return 1;
  draw_xpm(map,&img,x,y);
  return 0;
}



int delete_xpm(xpm_map_t xmap, uint16_t x, uint16_t y){
  uint8_t *map;
  xpm_image_t img;
  map = xpm_load(xmap,XPM_8_8_8,&img);
  if(map == NULL) return 1;
  for(unsigned int i=0; i<img.height; i++){
    for(unsigned int j= 0; j<img.width; j++){
      vg_draw_pixel(x + j, y + i, 0);
    }
  }
  return 0;
}

int video_move_consecutiveFramesDisplacement(xpm_map_t xpm, uint16_t *x, uint16_t *y, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,int16_t speed, uint8_t fr_rate){
  speed = abs(speed);

  /*if there is a frame to show and there is at least one movement to do in one of the axis (before the final position)*/
  if(COUNTER%(60/fr_rate) == 0 && ((*x<xf && yi==yf && xi<=xf)||( *y<yf && xi == xf && yi<=yf)||(*x>xf && yi==yf && xi>xf)||( *y>yf && xi == xf && yi>yf))){ 
    if(delete_xpm(xpm,*x,*y)!=0) return 1;//clean the last frame
        
    if(xi==xf){
      if(yf>yi)
        *y= *y + speed;
      else{
        *y= *y - speed;
      }
    } /*if the movement is in y axis move speed pixels in that axis- displacement in pixels between consecutive frames*/
    else if(yi==yf){
      if(xf>=xi)
        *x= *x + speed;
      else{
        *x= *x - speed;
      }
    }/*if the movement is in x axis move speed pixels in that axis- displacement in pixels between consecutive frames*/
        
    if((*x>xf && yi==yf && xi<=xf) ||(*y>yf && xi==xf && yi<=yf)||(*y<yf && xi==xf && yi>yf) || (*x<xf && yi==yf && xi>xf)){/* if we are in the final position*/
      if(get_xpm(xpm,xf,yf) != 0) return 1;
      return 2;
    }
    else
    {
      if(get_xpm(xpm,*x,*y)!= 0) return 1;
    }
  }				
  return 0;
}



int get_current_buffer(reg86_t *r) {

  r->ax = 0x4F07;
  r->bx = 0x01;
  r->intno = 0x10;

  if (sys_int86(r) != OK) {
    printf("\tgetCurrentBUffer(): sys_int86() failed \n");
    return -1;
  }

  return 0;
}

int swap_buffer() {

  reg86_t r;

  memset(&r, 0, sizeof(reg86_t));

  get_current_buffer(&r);

  if (r.dx == 0) {
    memset(&r, 0, sizeof(reg86_t));
    r.dx = v_res;
  }
  else if (r.dx == v_res){
    memset(&r, 0, sizeof(reg86_t));
    r.dx = 2*v_res;
  }else{
    memset(&r, 0, sizeof(reg86_t));
    r.dx = 0;
  }

  r.ax = 0x4F07;
  r.bx = 0x00;
  r.cx = 0x00;
  r.intno = 0x10;

  if (sys_int86(&r) != OK) {
    printf("\tsetCurrentBUffer(): sys_int86() failed \n");
    return -1;
  }

  char *temp = video_mem;
  video_mem = video_mem_sec;
  video_mem_sec = temp;
  return 0;
}

