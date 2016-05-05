#include <imgui.h>
#include "gui.h"

struct GUIState gui_state = {
    .imgui_metrics_window_open = false,
    .xe_metrics_window_open = false,

    .render_mnormals = false,
    .render_datastructures = false,
    .render_wireframe = false,
};

void render_gui() {
    render_main_menubar();
    if (gui_state.imgui_metrics_window_open) ImGui::ShowMetricsWindow(&gui_state.imgui_metrics_window_open);
    if (gui_state.xe_metrics_window_open) {}
}

static void render_main_menubar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("View")) {
            render_mmb_view();
        }
        ImGui::EndMainMenuBar();
    }
}

static void render_mmb_view() {
    if (ImGui::BeginMenu("Visuals")) {
        ImGui::MenuItem("Render mesh normals", NULL, &gui_state.render_mnormals);
        ImGui::MenuItem("Render datastructure overlays", NULL, &gui_state.render_datastructures);
        ImGui::MenuItem("Render as wireframes", NULL, &gui_state.render_wireframe);
        ImGui::EndMenu();
    }
    ImGui::MenuItem("IMGUI Metrics", NULL, &gui_state.imgui_metrics_window_open);
    ImGui::MenuItem("xe metrics", NULL, &gui_state.xe_metrics_window_open);

    ImGui::EndMenu();
}
