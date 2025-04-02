#ifndef _UI_CODE_HPP
#define _UI_CODE_HPP

#include <lvgl.h>
// #include <SPI.h>
// #include <Wire.h>
#include "lgfx.hpp"

#define TFT_BL 2
//define i2c
//#define can


static LGFX lcd;
//static SPIClass& spi = SPI;



/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[800 * 480 / 10];
//static lv_color_t disp_draw_buf;
static lv_disp_drv_t disp_drv;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void init_screen();
#endif