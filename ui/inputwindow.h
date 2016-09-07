#ifndef __UI_INPUTWINDOW_H__
#define __UI_INPUTWINDOW_H__

#include <vector>

#include <imgui.h>
#include <GLFW/glfw3.h>

#include "ui/util.h"
#include "services/locator.h"

static void render_input_window(const char *title, bool *opened) {
	ImGui::SetNextWindowSize(ImVec2(400,300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin(title, opened);

	std::vector<Joystick*> controllers = services::Locator::getInput().getControllers();
	ImGui::ListBoxHeader("Plugged controllers", controllers.size(), 4);
	for (auto j : controllers) {
		if (ImGui::Selectable(j->dump().c_str(), j->enabled))
			j->enabled = !j->enabled;
	}
	ImGui::ListBoxFooter();
    ImGui::SameLine(); ui::ShowHelpMarker("Click controllers to activate them.");

	ImGui::End();
}

#endif