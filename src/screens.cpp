#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"
#include "sensors.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void set_temp(void *obj, int32_t v) {

    float temp = read_temperature();
    char buf[32];
    lv_snprintf(buf, sizeof(buf), "Temp: %.1f*C", temp);
    lv_label_set_text((lv_obj_t*)obj, buf);

    // Update the temperature value on the arc.
    lv_arc_set_value(objects.temp_ark, temp);
    
}

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_settingssss_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_calendar_create(parent_obj);
            lv_obj_set_pos(obj, 34, 260);
            lv_obj_set_size(obj, 253, 272);
            lv_calendar_header_arrow_create(obj);
            lv_calendar_set_today_date(obj, 2025, 3, 13);
            lv_calendar_set_showed_date(obj, 2025, 3);
        }
        {
            lv_obj_t *obj = lv_roller_create(parent_obj);
            lv_obj_set_pos(obj, 34, 16);
            lv_obj_set_size(obj, 135, 85);
            lv_roller_set_options(obj, "Option 1\nOption 2\nOption 3", LV_ROLLER_MODE_NORMAL);
        }
        {
            lv_obj_t *obj = lv_chart_create(parent_obj);
            lv_obj_set_pos(obj, 34, 112);
            lv_obj_set_size(obj, 253, 128);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 189, 25);
            lv_obj_set_size(obj, 107, 53);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Button");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
}

void create_screen_settingssss() {
    void *flowState = getFlowState(0, 1);
    lv_obj_t *obj = lv_obj_create(0);
    objects.settingssss = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 26, 54);
            lv_obj_set_size(obj, 100, 50);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Button");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 160, 54);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_settingssss_obj1, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Button");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            lv_obj_set_pos(obj, 34, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "Checkbox");
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            lv_obj_set_pos(obj, 35, 165);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "Checkbox");
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            lv_obj_set_pos(obj, 149, 113);
            lv_obj_set_size(obj, 154, 172);
            lv_arc_set_value(obj, 50);
            lv_arc_set_bg_start_angle(obj, 0);
            lv_arc_set_bg_end_angle(obj, 180);
            lv_arc_set_rotation(obj, 180);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 36, 19);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Text");
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            lv_obj_set_pos(obj, 34, 201);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(4278190335));
            lv_led_set_brightness(obj, 255);
        }
    }
}

void tick_screen_settingssss() {
    void *flowState = getFlowState(0, 1);
}

void create_screen_temp() {
    void *flowState = getFlowState(0, 2);
    lv_obj_t *obj = lv_obj_create(0);
    objects.temp = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // temp_ark
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.temp_ark = obj;
            lv_obj_set_pos(obj, 67, 28);
            lv_obj_set_size(obj, 187, 184);
            lv_arc_set_range(obj, 0, 40);
            lv_arc_set_value(obj, 20);
            lv_arc_set_bg_start_angle(obj, 0);
            lv_arc_set_bg_end_angle(obj, 180);
            lv_arc_set_rotation(obj, 180);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff6a6a73), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff191a1a), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffd6d9dc), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temp_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_label = obj;
            lv_obj_set_pos(obj, 0, 108);
            lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Temp: 99.9*C");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff314a4a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            // lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Create an animation to update with the latest temperature value every 10 seconds
            lv_anim_t a_temp;
            lv_anim_init(&a_temp);
            lv_anim_set_exec_cb(&a_temp, set_temp);
            lv_anim_set_duration(&a_temp, 10*1000);
            lv_anim_set_playback_duration(&a_temp, 10*1000);
            lv_anim_set_var(&a_temp, obj);
            lv_anim_set_values(&a_temp, 0, 100);
            lv_anim_set_repeat_count(&a_temp, LV_ANIM_REPEAT_INFINITE);
            lv_anim_start(&a_temp);
        }
    }
}

void tick_screen_temp() {
    void *flowState = getFlowState(0, 2);
}


static const char *screen_names[] = { "Main", "settingssss", "temp" };
static const char *object_names[] = { "main", "settingssss", "temp", "obj0", "obj1", "temp_ark", "temp_label" };

void create_screens() {
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_settingssss();
    create_screen_temp();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_settingssss,
    tick_screen_temp,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
