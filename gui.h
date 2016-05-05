#ifndef __GUI_H__
#define __GUI_H__

static void render_main_menubar();
static void render_mmb_view();

struct GUIState {
    bool imgui_metrics_window_open;
    bool xe_metrics_window_open;

    bool render_mnormals;
    bool render_datastructures;
    bool render_wireframe;
};
extern struct GUIState gui_state;

void render_gui();

#endif
