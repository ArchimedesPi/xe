#include "input.h"

void Joystick::updateMetadata() {
	this->name = std::string(glfwGetJoystickName(this->index));
}

std::string Joystick::dump() {
	return std::to_string(this->index) + ": " + this->name;
}
