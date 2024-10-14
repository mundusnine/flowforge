#include "ui.h"

#include "imgui.h"
#include "imgui_internal.h"// For SeparatoEx
#include "rlImGui.h"
#include <string>
#include <float.h>
#include "extras/FA6FreeSolidFontData.h"

ImFont* big_icon_font;
void rlimgui_load_big_icons(void){
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = false;

    icons_config.GlyphMaxAdvanceX = FLT_MAX;
    icons_config.RasterizerMultiply = 1.0f;
    icons_config.OversampleH = 2;
    icons_config.OversampleV = 1;

    icons_config.GlyphRanges = icons_ranges;

    ImGuiIO& io = ImGui::GetIO();
    icons_config.MergeMode = false;
    big_icon_font = io.Fonts->AddFontFromMemoryCompressedTTF((void*)fa_solid_900_compressed_data, fa_solid_900_compressed_size, 48, &icons_config, icons_ranges);
    rlImGuiReloadFonts();
}

void ui_init(UI_Data* data){
    rlImGuiSetup(true);
    rlimgui_load_big_icons();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void ui_update(UI_Data* data){

}
#define CREATE_CMD "Create command"
int draw_subelements(commands* cmds){
    ImGui::Indent();
    for(int i =0; i < cmds->count;++i){
        command_t* cmd = cmds->items[i];
        if(cmd->type == OP_FUNCCALL){
            char* label = command_as_string(cmd);
            ImGui::Selectable(ICON_FA_ARROW_RIGHT_ARROW_LEFT " Call");
            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();
            ImGui::Text(label);
            if(ImGui::Button(ICON_FA_CIRCLE_PLUS " command")){
                ImGui::OpenPopup(CREATE_CMD);
            }
        }
    }
    ImGui::Unindent();
    if(ImGui::BeginPopupModal(CREATE_CMD,NULL,ImGuiWindowFlags_AlwaysAutoResize)){
        int shouldClose = 0;
        ImGui::Text("This is a modal window.");
        ImGui::Separator();
        ImGui::Text("You can put any content here.");
        if(ImGui::Button("Close")){
            shouldClose = 1;
        }
        ImGui::SameLine();
        if(ImGui::Button("Create")){
            shouldClose = 1;
        }
        if(shouldClose){
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    return 0;
}

static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
#define DOCKSPACE "Dockspace" 
#define WINDOW_1 "FlowForge"
#define WINDOW_2 "Execution Test"
void CreateDockedWindows(UI_Data* data, ImGuiID dockspace_id)
{
    ImGui::DockBuilderRemoveNode(dockspace_id);
    ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, ImVec2(data->screen_w,data->screen_h));

    ImGuiID window1_id = ImGui::DockBuilderAddNode(ImGui::GetID(WINDOW_1), ImGuiDockNodeFlags_None);
    ImGuiID window2_id = ImGui::DockBuilderAddNode(ImGui::GetID(WINDOW_2), ImGuiDockNodeFlags_None);

    ImGuiID dock_id_left  = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.5f, &window1_id, &dockspace_id);
    
    ImGui::DockBuilderDockWindow(WINDOW_1, dock_id_left);
    ImGui::DockBuilderDockWindow(WINDOW_2, dockspace_id);

    ImGui::DockBuilderFinish(dockspace_id);
}

void ui_draw(UI_Data* data){
    rlImGuiBegin();
    
    ImGui::Begin(DOCKSPACE,NULL,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
    ImGuiID dockspace_id =  ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoUndocking);
    static bool is_init = true;
    if(is_init){
        CreateDockedWindows(data,dockspace_id);
        is_init = false;
    }
    ImGui::End();


    static bool is_open = true;
    ImGui::Begin(WINDOW_1);
    ImGui::PushFont(big_icon_font);
    const char* icon = data->is_running ? ICON_FA_CIRCLE_STOP: ICON_FA_CIRCLE_PLAY; 
    int text_w = MeasureText(icon,big_icon_font->FontSize) * 1.65f;
    ImVec2 size = ImVec2(text_w,big_icon_font->FontSize);
    if(ImGui::Selectable(icon,false,0,size)){
        data->is_running = !data->is_running;
    }
    ImGui::PopFont();

    ImGui::Text("Code Section:");
    ImGui::Separator();
    ImGui::BeginDisabled(data->is_running);
    draw_subelements(&data->root.sub_cmds);

    ImGui::EndDisabled();
    ImGui::End();
    ImGui::Begin(WINDOW_2);
    ImGui::Text("This is a test");
    ImGui::End();

    rlImGuiEnd();
}
void ui_shutdown(UI_Data* data){

}