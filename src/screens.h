#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *settingssss;
    lv_obj_t *temp;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *temp_ark;
    lv_obj_t *temp_label;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SETTINGSSSS = 2,
    SCREEN_ID_TEMP = 3,
};

void create_screen_main();
void tick_screen_main();

void create_screen_settingssss();
void tick_screen_settingssss();

void create_screen_temp();
void tick_screen_temp();

void create_screens();
void tick_screen(int screen_index);

static void set_temp(void *obj, int32_t v);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/