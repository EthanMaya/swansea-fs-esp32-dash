#include <lvgl.h>
#include <ESP32-TWAI-CAN.hpp>
#include "ui_code.hpp"
#include "ui.h"

#define CAN_TX 44
#define CAN_RX 43
#define SPEED 1000
#define HAS_DISPLAY 1
//#define P 43
//works   38 44 43
//doesn't 19
typedef u_int8_t u8;
typedef u_int16_t u16;
CanFrame rxFrame;

void setup()
{


  auto SUCCESS = 
      ESP32Can.begin(ESP32Can.convertSpeed(SPEED), CAN_TX, CAN_RX, 10, 10);
    if (SUCCESS) {
      Serial.println("CAN bus started!");
    } else {
      Serial.println("CAN bus failed!");
    }
    
#if (HAS_DISPLAY)
    init_screen();
  #endif
}

#if (HAS_DISPLAY)
lv_obj_t **e_Throttle_Bar = &ui_Bar2;
lv_obj_t **e_Throttle_Num = &ui_Label7;
lv_obj_t **e_Gear_Position = &ui_Label8;
lv_obj_t **e_Temperature = &ui_Label5;
lv_obj_t **e_Pressure = &ui_Label6;
int y = 0;
#endif

u16 throttle = 0;
u8 temperature = 0;
u8 pressure = 0;
u8 gear = -1;
u8 temp = 0;
void loop()
{ //while
  //0x360 rpm 0-1
  //0x360 throttle 4-5
  //0x361 oil press 0-1
  //0x3E0 6-7 oil temp
  //0x470 6 gear selector position
  auto SUCCESS = 
      ESP32Can.begin(ESP32Can.convertSpeed(SPEED), CAN_TX, CAN_RX, 10, 10);
  u8 temp = rxFrame.identifier;
  ESP32Can.end();
  Serial.begin(9600);
  Serial.println(temp);
  Serial.println("Serial");
  Serial.end();

  


  // boolean nothingToOutput = true;
  // while (nothingToOutput) {
  //   Serial.println("No output");
  //   if (ESP32Can.readFrame(rxFrame, 1000))
  //   {
  //     Serial.println(rxFrame.identifier);

  //     if (rxFrame.identifier == 0x360) { //rpm
  //       u16 bit0 = rxFrame.data[4];
  //       u16 bit1 = rxFrame.data[5];
  //       throttle = (bit0 << 8) | bit1;
  //       throttle /= 10;
  //       nothingToOutput = false;
  //     }
  //     if (rxFrame.identifier == 0x471) { //rpm
  //       u16 bit0 = rxFrame.data[2];
  //       u16 bit1 = rxFrame.data[3];
  //       temperature = (bit0 << 8) | bit1;
  //       temperature /= 10;
  //       nothingToOutput = false;
  //     }
  //     if (rxFrame.identifier == 0x361) { //oil press
  //       temperature = rxFrame.data[1];
  //     }
  //     if (rxFrame.identifier == 0x3E0) {//oil temp
  //       gear = rxFrame.data[2];
  //     }
  //     if (rxFrame.identifier == 0x470) { //gear sel
  //       pressure = rxFrame.data[3];
  //     }
  //     //Serial.printf("ID: %d", rxFrame.identifier);
  //     Serial.printf("Throttle %d \r\n", throttle);
  //     Serial.printf("Temperature %d \r\n", temperature);
  //     Serial.printf("Gear %d \r\n", gear);
  //     Serial.printf("Pressure %d \r\n\n", pressure);
  //   }
  //   nothingToOutput = false;
  // }

#if (HAS_DISPLAY)
    char buf[16];
    lv_snprintf(buf, sizeof(buf), "%d", throttle);
    lv_label_set_text(*e_Throttle_Num, buf);
    lv_bar_set_value(*e_Throttle_Bar, throttle, LV_ANIM_OFF);
    lv_snprintf(buf, sizeof(buf), "%d", temperature);
    lv_label_set_text(*e_Temperature, buf);
    lv_snprintf(buf, sizeof(buf), "%d", gear);
    lv_label_set_text(*e_Gear_Position, buf);
    lv_snprintf(buf, sizeof(buf), "%d", pressure);
    lv_label_set_text(*e_Pressure, buf);
    

    // temp++;

    // Serial1.println(temp);

    // Serial1.println("before GUI");

    lv_timer_handler(); /* let the GUI do its work */
    //Serial1.println("After GUI");
    //digitalWrite(P, HIGH);
    //delay(1000);
    //digitalWrite(P, LOW);
    delay(10);
#endif


}

// #include "ui.h"
// #include "ui_code.hpp"
// #include <ESP32-TWAI-CAN.hpp>

// #define CAN_TX 5
// #define CAN_RX 4
// #define SPEED 1000
// #define HAS_DISPLAY 1
// typedef u_int8_t u8;

// CanFrame rxFrame;

// void setup() {
//   Serial.begin(9600);
// #if (HAS_DISPLAY)
//   init_screen();
// #endif
//   auto SUCCESS =
//       ESP32Can.begin(ESP32Can.convertSpeed(SPEED), CAN_TX, CAN_RX, 10, 10);

//   if (SUCCESS) {
//     Serial.println("CAN bus started!");
//   } else {
//     Serial.println("CAN bus failed!");
//   }
// }

// #if (HAS_DISPLAY)
// lv_obj_t **e_Throttle_Bar = &ui_Bar2;
// lv_obj_t **e_Throttle_Num = &ui_Label7;
// lv_obj_t **e_Gear_Position = &ui_Label8;
// lv_obj_t **e_Temperature = &ui_Label5;
// lv_obj_t **e_Pressure = &ui_Label6;
// int y = 0;
// #endif

// u8 throttle = 0;
// u8 temperature = 0;
// u8 pressure = 0;
// u8 gear = -1;

// void loop() {

//   if (ESP32Can.readFrame(rxFrame, 1000)) {
//     throttle = rxFrame.data[0];
//     temperature = rxFrame.data[1];
//     gear = rxFrame.data[2];
//     pressure = rxFrame.data[3];

//     Serial.printf("Throttle %d \r\n", throttle);
//     Serial.printf("Temperature %d \r\n", temperature);
//     Serial.printf("Gear %d \r\n", gear);
//     Serial.printf("Pressure %d \r\n\n", pressure);
//   }

// #if (HAS_DISPLAY)
//   char buf[16];
//   if (y >= 100) {
//     lv_snprintf(buf, sizeof(buf), "%d", throttle);
//     lv_label_set_text(*e_Throttle_Num, buf);
//     lv_bar_set_value(*e_Throttle_Bar, throttle, LV_ANIM_OFF);
//     throttle++;
//     y = -1;
//   }
//   y++;
//   lv_timer_handler(); /* let the GUI do its work */
// #endif
// }
