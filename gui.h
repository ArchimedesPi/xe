#ifndef __GUI_H__
#define __GUI_H__

#include <imgui.h>
#include "ui/logwindow.h"

static void render_main_menubar();
static void render_mmb_view();
static void render_mmb_file();

struct GUIState {
    bool imgui_test_window_open;

    bool imgui_metrics_window_open;
    bool xe_metrics_window_open;

    bool log_window_open;

    bool render_mnormals;
    bool render_datastructures;
    bool render_wireframe;
};
extern struct GUIState gui_state;

extern ui::LogWindow* log_window;

void setup_gui();
void render_gui();

#endif
