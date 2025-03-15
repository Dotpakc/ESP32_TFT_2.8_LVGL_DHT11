#include <Arduino.h>
//---------------------------------------- Including Libraries.
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "ui.h"
#include "screens.h"
//---------------------------------------- 
#include "sensors.h"

// Defines the T_CS Touchscreen PIN.
#define T_CS_PIN  22 //--> T_CS

// Defines the PIN for the LED.
// DELETE OR COMMENT OUT THE LINES OF CODE BELOW IF YOU DON'T WANT TO USE LEDS.
#define LED_PIN   27

// Defines the width and height of the screen.
#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

// Variables for x, y and z values ​​on the touchscreen.
int x, y, z;

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

//---------------------------------------- Global variables for objects or widgets.
static lv_obj_t * btn_Count, * btn_Count_Label;
int btn_Count_Val = 0;

static lv_obj_t * btn_Toggle, * btn_Toggle_Label;

static lv_obj_t * slider_label;
//---------------------------------------- 

// Variables for PWM settings.
// In this project, PWM is used to control the LED.
// DELETE OR COMMENT OUT THE LINES OF CODE BELOW IF YOU DON'T WANT TO USE LEDS.
const int PWM_CHANNEL = 0;    // ESP32 has 16 channels which can generate 16 independent waveforms.
const int PWM_FREQ = 5000;    // Frequency in Hz. Official ESP32 example uses 5,000Hz.
const int PWM_RESOLUTION = 8; // 8 bits PWM resolution(0-255). But ESP32 can go up to 16 bits.

// Declaring the "XPT2046_Touchscreen" object as "touchscreen" and its settings.
XPT2046_Touchscreen touchscreen(T_CS_PIN);



//________________________________________________________________________________ log_print()
// If logging is enabled, it will inform the user about what is happening in the library.
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
//________________________________________________________________________________ 



//________________________________________________________________________________ touchscreen_read()
// Get the Touchscreen data.
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
  if(touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    
    // Calibrate Touchscreen points with map function to the correct width and height.
    x = map(p.x, 230, 3920, 1, SCREEN_WIDTH);
    y = map(p.y, 400, 3905, 1, SCREEN_HEIGHT);
    z = p.z;

    data->state = LV_INDEV_STATE_PRESSED;

    // Set the coordinates.
    data->point.x = x;
    data->point.y = y;

    // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor.
    /*Serial.print("X = ");
    Serial.print(x);
    Serial.print(" | Y = ");
    Serial.print(y);
    Serial.print(" | Pressure = ");
    Serial.print(z);
    Serial.println();*/
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ event_handler_btn_Count()
// Callback that is triggered when "btn_Count" is clicked.
static void event_handler_btn_Count(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  
  if(code == LV_EVENT_CLICKED) {
    btn_Count_Val++;

    lv_obj_t * new_btn_Count_Label = lv_obj_get_child(btn_Count, 0);
    lv_label_set_text_fmt(new_btn_Count_Label, "Btn Count : %d", btn_Count_Val);
    
    LV_LOG_USER("Button Count clicked, Count : %d.\n", (int)btn_Count_Val);
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ event_handler_btn_Toggle()
// Callback that is triggered when "btn_Toggle" is clicked/toggled.
static void event_handler_btn_Toggle(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = (lv_obj_t*) lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    LV_UNUSED(obj);

    bool checked = lv_obj_has_state(obj, LV_STATE_CHECKED);

    static lv_style_t style_New_Bg_Color;
    lv_style_init(&style_New_Bg_Color);

    lv_obj_t * new_btn_Toggle_Label = lv_obj_get_child(btn_Toggle, 0);
    
    if (checked == true) {
      lv_style_set_bg_color(&style_New_Bg_Color, lv_color_make(255, 0, 0));
      lv_label_set_text_fmt(new_btn_Toggle_Label, "Toggled : Off");
      
      // Turn on the LED.
      // DELETE OR COMMENT OUT THE LINES OF CODE BELOW IF YOU DON'T WANT TO USE LEDS.
      ledcWrite(PWM_CHANNEL, 255);
    } else {
      lv_style_set_bg_color(&style_New_Bg_Color, lv_color_make(0, 128, 0));
      lv_label_set_text_fmt(new_btn_Toggle_Label, "Toggled : On");
      
      // Turn off the LED.
      // DELETE OR COMMENT OUT THE LINES OF CODE BELOW IF YOU DON'T WANT TO USE LEDS.
      ledcWrite(PWM_CHANNEL, 0);
    }
    
    lv_obj_add_style(btn_Toggle, &style_New_Bg_Color, 0);
    
    LV_LOG_USER("Toggled : %s.\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ event_handler_Switch()
// Callback that is triggered when "Switch" is clicked/toggled.
static void event_handler_Switch(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = (lv_obj_t*) lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    LV_UNUSED(obj);

    bool checked = lv_obj_has_state(obj, LV_STATE_CHECKED);

    if (checked == true) {
      // Turn on the LED.
      // DELETE OR COMMENT OUT THE LINES OF CODE BELOW IF YOU DON'T WANT TO USE LEDS.
      ledcWrite(PWM_CHANNEL, 255);
    } else {
      // Turn on the LED.
      // DELETE OR COMMENT OUT THE LINES OF CODE BELOW IF YOU DON'T WANT TO USE LEDS.
      ledcWrite(PWM_CHANNEL, 0);
    }
    
    LV_LOG_USER("State: %s.\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ slider_event_callback()
// Callback that prints the current slider value on the TFT display and Serial Monitor for debugging purposes.
static void slider_event_callback(lv_event_t * e) {
  lv_obj_t * slider = (lv_obj_t*) lv_event_get_target(e);
  char buf[8];
  lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
  lv_label_set_text(slider_label, buf);
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  LV_LOG_USER("Slider changed to %d%%.\n", (int)lv_slider_get_value(slider));
  
  // Control LED brightness with Slider.
  // DELETE OR COMMENT OUT THE LINES OF CODE BELOW IF YOU DON'T WANT TO USE LEDS.
  int PWM_Val = map((int)lv_slider_get_value(slider), 0, 100, 0, 255);
  ledcWrite(PWM_CHANNEL, PWM_Val);
}
//________________________________________________________________________________ 



// //________________________________________________________________________________ lv_create_main_gui()
// void lv_create_main_gui(void) {
//   //---------------------------------------- Set the screen background color.
//   // Without this line of code, the default screen background color is white.
//   lv_obj_set_style_bg_color(lv_scr_act(), LV_COLOR_MAKE(255,255,255), LV_PART_MAIN);
//   //---------------------------------------- 

//   //---------------------------------------- Create text with a "span" aligned center on top ("ESP32 + TFT LCD Touchscreen ILI9341 + LVGL").
//   lv_obj_t *spans = lv_spangroup_create(lv_screen_active());
//     lv_obj_set_style_text_align(spans, LV_TEXT_ALIGN_CENTER, 0);
//     lv_obj_set_width(spans, 300);
//     lv_spangroup_set_mode(spans, LV_SPAN_MODE_BREAK);
//     lv_obj_align(spans, LV_ALIGN_TOP_MID, 0, 20);

//     // Створення першого span (текстового фрагмента)
//     lv_span_t *span1 = lv_spangroup_new_span(spans);
//     lv_span_set_text(span1, "ESP32 + ");

//     // Створення другого span з іншим стилем
//     lv_span_t *span2 = lv_spangroup_new_span(spans);
//     lv_span_set_text(span2, "TFT LCD Touchscreen ");
//     lv_style_set_text_color(lv_span_get_style(span2), lv_palette_main(LV_PALETTE_RED)); // Червоний текст

//     // Створення третього span
//     lv_span_t *span3 = lv_spangroup_new_span(spans);
//     lv_span_set_text(span3, "ILI9341 + ");

//     // Створення четвертого span з іншим стилем
//     lv_span_t *span4 = lv_spangroup_new_span(spans);
//     lv_span_set_text(span4, "LVGL");
//     lv_style_set_text_color(lv_span_get_style(span4), lv_palette_main(LV_PALETTE_BLUE)); // Синій текст
//   //---------------------------------------- 

//   //---------------------------------------- Create a Button (btn_Count).
//   btn_Count = lv_button_create(lv_screen_active());
//   lv_obj_add_event_cb(btn_Count, event_handler_btn_Count, LV_EVENT_ALL, NULL);
//   lv_obj_align(btn_Count, LV_ALIGN_TOP_LEFT, 20, 85);
//   lv_obj_remove_flag(btn_Count, LV_OBJ_FLAG_PRESS_LOCK);

//   // Set button color.
//   static lv_style_t btn_Count_Bg_Color;
//   lv_style_init(&btn_Count_Bg_Color);
//   lv_style_set_bg_color(&btn_Count_Bg_Color, lv_color_make(160, 32, 240));
//   lv_obj_add_style(btn_Count, &btn_Count_Bg_Color, 0);

//   btn_Count_Label = lv_label_create(btn_Count);
//   lv_label_set_text(btn_Count_Label, "Btn Count : 0");
//   lv_obj_center(btn_Count_Label);

//   // For more customized buttons, see here : 
//   // - https://docs.lvgl.io/master/examples.html#create-styles-from-scratch-for-buttons
//   // - https://docs.lvgl.io/master/widgets/button.html
//   //---------------------------------------- 

//   //---------------------------------------- Create a Toggle button (btn_Toggle).
//   btn_Toggle = lv_button_create(lv_screen_active());
//   lv_obj_add_event_cb(btn_Toggle, event_handler_btn_Toggle, LV_EVENT_ALL, NULL);
//   lv_obj_align(btn_Toggle, LV_ALIGN_TOP_RIGHT, -20, 85);
//   lv_obj_add_flag(btn_Toggle, LV_OBJ_FLAG_CHECKABLE);
//   lv_obj_set_height(btn_Toggle, LV_SIZE_CONTENT);

//   // Set button color.
//   static lv_style_t btn_Toggle_Bg_Color;
//   lv_style_init(&btn_Toggle_Bg_Color);
//   lv_style_set_bg_color(&btn_Toggle_Bg_Color, lv_color_make(0, 128, 0));
//   lv_obj_add_style(btn_Toggle, &btn_Toggle_Bg_Color, 0);

//   btn_Toggle_Label = lv_label_create(btn_Toggle);
//   lv_label_set_text(btn_Toggle_Label, "Toggled : On");
//   lv_obj_center(btn_Toggle_Label);
//   //---------------------------------------- 

//   //---------------------------------------- Create a Switch button (my_Switch).
//   lv_obj_t * my_Switch;
//   my_Switch = lv_switch_create(lv_screen_active());
//   lv_obj_add_event_cb(my_Switch, event_handler_Switch, LV_EVENT_ALL, NULL);
//   lv_obj_align(my_Switch, LV_ALIGN_TOP_MID, 0, 135);
//   lv_obj_set_style_bg_color(my_Switch, lv_color_make(204, 204, 204), 0);  //--> Set the switch indicator color when "off".
//   lv_obj_set_style_bg_color(my_Switch, lv_color_make(0,128,128), LV_PART_INDICATOR | LV_STATE_CHECKED); //--> Set the switch indicator color when "on".
//   lv_obj_clear_state(my_Switch, LV_STATE_CHECKED);
//   //---------------------------------------- 
  
//   //---------------------------------------- Create a slider aligned in the center bottom of the TFT display.
//   lv_obj_t * slider = lv_slider_create(lv_screen_active());
//   lv_obj_align(slider, LV_ALIGN_TOP_MID, 0, 185);
//   lv_obj_add_event_cb(slider, slider_event_callback, LV_EVENT_VALUE_CHANGED, NULL);
//   lv_slider_set_range(slider, 0, 100);
//   lv_obj_set_style_anim_duration(slider, 2000, 0);

//   // Create a label below the slider to display the current slider value.
//   slider_label = lv_label_create(lv_screen_active());
//   lv_label_set_text(slider_label, "0%");
//   lv_obj_align_to(slider_label, slider, LV_ALIGN_TOP_MID, 0, 20);
//   //---------------------------------------- 


//   /*Create a chart*/
//   lv_obj_t * chart;
//   chart = lv_chart_create(lv_screen_active());
//   lv_obj_set_size(chart, 200, 150);
//   lv_obj_center(chart);
//   lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

//   /*Add two data series*/
//   lv_chart_series_t * ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
//   lv_chart_series_t * ser2 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_SECONDARY_Y);
//   int32_t * ser2_y_points = lv_chart_get_y_array(chart, ser2);

//   uint32_t i;
//   for(i = 0; i < 10; i++) {
//       /*Set the next points on 'ser1'*/
//       lv_chart_set_next_value(chart, ser1, lv_rand(10, 50));

//       /*Directly set points on 'ser2'*/
//       ser2_y_points[i] = lv_rand(50, 90);
//   }

//   lv_chart_refresh(chart); /*Required after direct set*/



// }
// //________________________________________________________________________________ 

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println();
  delay(3000);

  Serial.println("ESP32 + TFT LCD Touchscreen ILI9341 + LVGL + EEZ Studio");
  Serial.println();
  delay(500);

  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(LVGL_Arduino);
  delay(500);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Start the DHT11 sensor.
  setup_sensors();
  //---------------------------------------- LVGL setup.
  Serial.println();
  Serial.println("Start LVGL Setup.");
  delay(500);
  

  // Start the SPI for the touchscreen and init the touchscreen.
  touchscreen.begin();

  // Set the Touchscreen rotation in landscape mode.
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 0. "touchscreen.setRotation(0);"
  touchscreen.setRotation(0);

  // Start LVGL.
  lv_init();
  
  // Register print function for debugging.
  lv_log_register_print_cb(log_print);

  // Create a display object.
  lv_display_t * disp;
  
  // Initialize the TFT display using the TFT_eSPI library.
  // draw_buf = new uint8_t[DRAW_BUF_SIZE];
  disp = lv_tft_espi_create( SCREEN_WIDTH,SCREEN_HEIGHT, draw_buf, DRAW_BUF_SIZE);
  // If the display on the TFT LCD has problems, try the line of code below:
  //disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, DRAW_BUF_SIZE);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
    
  // Initialize an LVGL input device object (Touchscreen).
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  
  // Set the callback function to read Touchscreen input.
  lv_indev_set_read_cb(indev, touchscreen_read);

  Serial.println();
  Serial.println("LVGL Setup Completed.");
  delay(500);
  //---------------------------------------- 

  // Integrate EEZ Studio GUI.
  ui_init();

  // // Register "my_button_test_bar" event handler.
  // lv_obj_add_event_cb(objects.my_button_test_bar, my_button_test_bar_event_handler, LV_EVENT_ALL, NULL);

  // // Register "my_button_toggle" event handler.
  // lv_obj_add_event_cb(objects.my_button_toggle, my_button_toggle_event_handler, LV_EVENT_ALL, NULL);

  //  // Register "my_switch" event handler.
  // lv_obj_add_event_cb(objects.my_switch, my_switch_event_handler, LV_EVENT_VALUE_CHANGED, objects.my_label_switch);

  // // Register "my_horizontal_slider" event handler.
  // lv_obj_add_event_cb(objects.my_horizontal_slider, my_horizontal_slider_value_changed_event_cb, LV_EVENT_VALUE_CHANGED, objects.my_label_horizontal_slider);

  // // Register "my_vertical_slider" event handler.
  // lv_obj_add_event_cb(objects.my_vertical_slider, my_vertical_slider_value_changed_event_cb, LV_EVENT_VALUE_CHANGED, objects.my_label_vertical_slider);

  // // Register "my_image_esp32" event handler.
  // lv_obj_add_event_cb(objects.my_image_esp32, my_image_esp32_event_handler, LV_EVENT_ALL, NULL);

  // // Register "my_image_lvgl" event handler.
  // lv_obj_add_event_cb(objects.my_image_lvgl, my_image_lvgl_event_handler, LV_EVENT_ALL, NULL);

  // // Register "my_image_eez" event handler.
  // lv_obj_add_event_cb(objects.my_image_eez, my_image_eez_event_handler, LV_EVENT_ALL, NULL);
}

// //________________________________________________________________________________ VOID SETUP()
// void setup() {
//   // put your setup code here, to run once:

//   Serial.begin(115200);
//   Serial.println();
//   delay(3000);

//   //---------------------------------------- PWM settings.
//   // Delete or comment out the lines of code in this section if you don't want to use LEDs.
  
//   // ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);
//   ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

//   // ledcAttachPin(uint8_t pin, uint8_t channel);
//   ledcAttachPin(LED_PIN, PWM_CHANNEL);
//   delay(500);
//   //---------------------------------------- 
  
//   Serial.println("ESP32 + TFT LCD Touchscreen ILI9341 320x240 + LVGL");
//   Serial.println();
  
//   String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
//   Serial.println(LVGL_Arduino);

//   // Start LVGL.
//   lv_init();
  
//   // Register print function for debugging.
//   lv_log_register_print_cb(log_print);

//   // Start the SPI for the touchscreen and init the touchscreen.
//   touchscreen.begin();

//   // Set the Touchscreen rotation in landscape mode.
//   // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 2. "touchscreen.setRotation(2);"
//   touchscreen.setRotation(0);

//   // Create a display object.
//   lv_display_t * disp;
  
//   // Initialize the TFT display using the TFT_eSPI library.
//   disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
//   lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
    
//   // Initialize an LVGL input device object (Touchscreen).
//   lv_indev_t * indev = lv_indev_create();
//   lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  
//   // Set the callback function to read Touchscreen input.
//   lv_indev_set_read_cb(indev, touchscreen_read);

//   // Function to draw the GUI (text, buttons and sliders).
//   lv_create_main_gui();
// }
// //________________________________________________________________________________ 


// Used to track the tick timer.
uint32_t lastTick = 0;
//________________________________________________________________________________ VOID LOOP()
void loop() {



  // put your main code here, to run repeatedly:
  ui_tick();
   lv_tick_inc(millis() - lastTick); //--> Update the tick timer. Tick is new for LVGL 9.
  lastTick = millis();
  lv_timer_handler(); //--> Update the UI.
  delay(2);

  // lv_task_handler();  // let the GUI do its work.
  // lv_tick_inc(5);     // tell LVGL how much time has passed.
  // delay(5);           // let this time pass.
}
