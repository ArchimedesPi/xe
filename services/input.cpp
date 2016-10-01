#include "input.h"

void Controller::updateMetadata() {
	this->name = std::string(glfwGetJoystickName(this->index));
}

std::string Controller::dump() {
	return std::to_string(this->index) + ": " + this->name;
}

