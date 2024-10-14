#include "entrypoint.h"
#include "ui.h"
#include "raylib.h"

#define KNOB_IMPLEMENTATION
#include "knob.h"

void raylib_start(void){
    InitWindow(960,540,"FlowForge");
    Image icon = LoadImage("assets/icons/icon.png");
    SetWindowIcon(icon);
    int width  = (int)(GetMonitorWidth(GetCurrentMonitor())* 0.75f);
    int height = (int)(GetMonitorHeight(GetCurrentMonitor()) * 0.75f);
    SetWindowPosition(GetMonitorWidth(GetCurrentMonitor()) * 0.5f - width * 0.5f,GetMonitorHeight(GetCurrentMonitor()) * 0.5f - height * 0.5f);
    SetWindowSize(width,height);
    SetTargetFPS(60);

    UI_Data data = {
        .bg_color = 0x181818FF,
        .screen_w = width,
        .screen_h = height,
    };
    // data.root
    command_t print = {
        .type = OP_FUNCCALL,
        .name = "print"
    };
    command_t value = {
        .type = OP_VALUE,
        .name = "S:Hello World !"
    };
    command_add_sub(&print,&value);
    command_add_sub(&data.root,&print);

    ui_init(&data);
    while(!WindowShouldClose()){
        ClearBackground(GetColor(data.bg_color));
        BeginDrawing();
        ui_draw(&data);
        EndDrawing();
    }

    CloseWindow();
}