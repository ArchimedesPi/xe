#pragma once
#include <vector>

#include <imgui.h>
#include <GLFW/glfw3.h>

#include "util.h"
#include "services/locator.h"

static void render_input_window(const char *title, bool *opened) {
	ImGui::SetNextWindowSize(ImVec2(400,300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin(title, opened);

	std::vector<Controller*> controllers = services::Locator::getInput().getControllers();
	ImGui::ListBoxHeader("Plugged controllers", controllers.size(), 4);
	for (auto j : controllers) {
		if (ImGui::Selectable(j->dump().c_str(), j->enabled))
			j->enabled = !j->enabled;
	}
	ImGui::ListBoxFooter();
    ImGui::SameLine(); ui::ShowHelpMarker("Click controllers to activate them.");

    if(ImGui::Button("Refresh controller list")) services::Locator::getInput().updateControllers();

	ImGui::End();
}
