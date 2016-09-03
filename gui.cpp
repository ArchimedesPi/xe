#include "gui.h"
#include <cstdlib>

ui::LogWindow* log_window;

void setup_gui() {
    log_window = new ui::LogWindow();
}

struct GUIState gui_state = {
    .imgui_test_window_open = false,

    .imgui_metrics_window_open = false,
    .xe_metrics_window_open = false,

    .log_window_open = false,
    .input_window_open = false,

    .render_mnormals = false,
    .render_datastructures = false,
    .render_wireframe = true,
};

void render_gui() {
    render_main_menubar();

    // demo
    if (gui_state.imgui_test_window_open) ImGui::ShowTestWindow(&gui_state.imgui_test_window_open);

    // metrics
    if (gui_state.imgui_metrics_window_open) ImGui::ShowMetricsWindow(&gui_state.imgui_metrics_window_open);
    if (gui_state.xe_metrics_window_open) {}

    // commands and logs
    if (gui_state.log_window_open) log_window->render("[log]", &gui_state.log_window_open);
    
    // tools
    if (gui_state.input_window_open) render_input_window("[input]", &gui_state.input_window_open);
}

static void render_main_menubar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File"))
            render_mmb_file();
        if (ImGui::BeginMenu("View"))
            render_mmb_view();
        if (ImGui::BeginMenu("Tools"))
            render_mmb_tools();
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
    ImGui::MenuItem("IMGUI Test", NULL, &gui_state.imgui_test_window_open);
    ImGui::MenuItem("IMGUI Metrics", NULL, &gui_state.imgui_metrics_window_open);
    ImGui::MenuItem("xe metrics", NULL, &gui_state.xe_metrics_window_open);
    ImGui::MenuItem("Log", NULL, &gui_state.log_window_open);

    ImGui::EndMenu();
}

static void render_mmb_tools() {
    ImGui::MenuItem("Input", NULL, &gui_state.input_window_open);

    ImGui::EndMenu();
}


static void render_mmb_file() {
    if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
        std::exit(0);
    }
    ImGui::EndMenu();
}

