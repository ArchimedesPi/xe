#include "input.h"

#include <stdio.h>

#include <GLFW/glfw3.h>

void Joystick::updateMetadata() {
	this->name = std::string(glfwGetJoystickName(this->index));
}

std::string Joystick::dump() {
	return std::to_string(this->index) + ": " + this->name;
}

std::vector<Joystick> Input::getJoysticks() {
	std::vector<Joystick> joysticks;
	for (int i=0; i<GLFW_JOYSTICK_LAST; i++) {
		if (glfwJoystickPresent(i) == GLFW_TRUE) {
			joysticks.push_back(Joystick(i));
		}
	}
	return joysticks;
}