#include "gui.h"
#include "ui/theme.h"
#include <cstdlib>

ui::LogWindow* log_window;


struct GUIState gui_state = {
    .imgui_test_window_open = false,

    .imgui_metrics_window_open = false,
    .xe_metrics_window_open = false,

    .input_window_open = false,
    .video_window_open = false,

    .dark_style = false,

    .render_mnormals = false,
    .render_datastructures = false,
    .render_wireframe = true,

    .scenegraph_window_open = false,
};

void setup_gui() {
    log_window = new ui::LogWindow();
    setup_ui_theme(gui_state.dark_style);
}

void render_gui() {
    render_main_menubar();

    // demo
    if (gui_state.imgui_test_window_open) ImGui::ShowTestWindow(&gui_state.imgui_test_window_open);

    // metrics
    if (gui_state.imgui_metrics_window_open) ImGui::ShowMetricsWindow(&gui_state.imgui_metrics_window_open);
    if (gui_state.xe_metrics_window_open) {}

    // options
    if (gui_state.input_window_open) render_input_window("[input]", &gui_state.input_window_open);
    if (gui_state.video_window_open) {}
}

static void render_main_menubar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File"))
            render_mmb_file();
        if (ImGui::BeginMenu("View"))
            render_mmb_view();
        //if (ImGui::BeginMenu("Tools"))
        //     render_mmb_tools();
        if (ImGui::BeginMenu("Options"))
            render_mmb_options();
        if (ImGui::BeginMenu("Debug"))
            render_mmb_debug();
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

    ImGui::EndMenu();
}

static void render_mmb_tools() {
    ImGui::EndMenu();
}

static void render_mmb_debug() {
    ImGui::MenuItem("View Scenegraph", NULL, &gui_state.scenegraph_window_open);
    ImGui::EndMenu();
}

static void render_mmb_file() {
    if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
        std::exit(0);
    }
    ImGui::EndMenu();
}

static void render_mmb_options() {
    auto &style = ImGui::GetStyle();
    ImGui::MenuItem("Input", NULL, &gui_state.input_window_open);
    ImGui::MenuItem("Video", NULL, &gui_state.video_window_open);
    ImGui::SliderFloat("GUI overlay opacity", &style.Alpha, 0.2f, 1.0f, "%.2f");
    if(ImGui::Checkbox("Dark mode", &gui_state.dark_style)) {
        set_ui_colors(gui_state.dark_style);
    }

    ImGui::EndMenu();
}
