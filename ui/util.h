#pragma once

#include <imgui.h>

namespace ui {
	static void ShowHelpMarker(const char* desc) {
	    ImGui::TextDisabled("(?)");
	    if (ImGui::IsItemHovered())
	        ImGui::SetTooltip(desc);
	}
}