#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_EXPLOSION_IMG
#define LV_ATTRIBUTE_IMG_EXPLOSION_IMG
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_EXPLOSION_IMG uint8_t explosion_img_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 1*/

  0x00, 0xc0, 0xc0, 0x00, 
  0x00, 0xc0, 0xc0, 0x00, 
  0x30, 0x33, 0x03, 0x00, 
  0x30, 0x33, 0x03, 0x00, 
  0x0c, 0x00, 0x0c, 0x00, 
  0x0c, 0x00, 0x0c, 0x00, 
  0x03, 0x00, 0x30, 0x00, 
  0x03, 0x00, 0x30, 0x00, 
  0xf0, 0x00, 0x03, 0xc0, 
  0xf0, 0x00, 0x03, 0xc0, 
  0x03, 0x00, 0x30, 0x00, 
  0x03, 0x00, 0x30, 0x00, 
  0x0c, 0x33, 0x0c, 0x00, 
  0x0c, 0x33, 0x0c, 0x00, 
  0x30, 0xc0, 0xc3, 0x00, 
  0x30, 0xc0, 0xc3, 0x00, 
};

const lv_img_dsc_t explosion_img = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 26,
  .header.h = 16,
  .data_size = 72,
  .data = explosion_img_map,
};
