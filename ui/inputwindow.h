#ifndef __UI_INPUTWINDOW_H__
#define __UI_INPUTWINDOW_H__

#include <imgui.h>

static void render_input_window(const char *title, bool *opened) {
	ImGui::SetNextWindowSize(ImVec2(400,300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin(title, opened);

	ImGui::End();
}

#endif