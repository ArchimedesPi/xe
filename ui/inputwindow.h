#ifndef __UI_INPUTWINDOW_H__
#define __UI_INPUTWINDOW_H__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include <imgui.h>

#include <GLFW/glfw3.h>

#include "input.h"

static void render_input_window(const char *title, bool *opened) {
	ImGui::SetNextWindowSize(ImVec2(400,300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin(title, opened);

	// because converting between a std::vector<std:string> and a const char*[]
	// is way harder than it needs to be
	auto joysticks = Input::getJoysticks();
	std::vector<const char*> joystick_descrs;
	for (Joystick j : joysticks) {
		std::string jd = j.dump().c_str();
		char *pc = new char[jd.size()+1];
		std::strcpy(pc, jd.c_str());
		joystick_descrs.push_back(pc);
	}

	static int listbox_selected = 0;
	ImGui::ListBox("Plugged controllers", &listbox_selected, &joystick_descrs[0], joystick_descrs.size(), 4);

	ImGui::End();
}

#endif