#ifndef __GUI_H__
#define __GUI_H__

#include <imgui.h>

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

class LogWindow {
public:
    LogWindow() {}
    void render(const char *title, bool *opened);
    void clear();

private:
    ImGuiTextBuffer buffer;
    bool scrolldown;
};

void render_gui();

#endif
