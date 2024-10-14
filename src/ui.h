#pragma once

#include "codegen.h"

typedef struct {
    unsigned int bg_color;
    int screen_w;
    int screen_h;
    int is_running;
    command_t root;
    int dnd_state;
    command_t* selected_item;
} UI_Data;

#ifdef __cplusplus
extern "C"{
#endif

void ui_init(UI_Data* data);
void ui_update(UI_Data* data);
void ui_draw(UI_Data* data);
void ui_shutdown(UI_Data* data);

#ifdef __cplusplus
}
#endif