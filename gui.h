#pragma once

#include <imgui.h>
#include "ui/logwindow.h"
#include "ui/inputwindow.h"

static void render_main_menubar();
static void render_mmb_view();
static void render_mmb_file();
static void render_mmb_tools();
static void render_mmb_options();
static void render_mmb_debug();

struct GUIState {
    bool imgui_test_window_open;

    bool imgui_metrics_window_open;
    bool xe_metrics_window_open;

    bool input_window_open;
    bool video_window_open;

    bool dark_style;

    bool render_mnormals;
    bool render_datastructures;
    bool render_wireframe;

    bool scenegraph_window_open;
};
extern struct GUIState gui_state;

extern ui::LogWindow *log_window;

void setup_gui();
void render_gui();
