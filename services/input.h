#pragma once

#include <string>
#include <vector>
#include <array>

#include <GLFW/glfw3.h>

class Joystick {
public:
	Joystick(int idx) : index(idx), enabled(false) {this->updateMetadata();}

	void updateMetadata();

	std::string dump();

	int index;
	std::string name;
	bool enabled;
};

namespace services {
	class Input {
	public:
		virtual std::vector<Joystick*> getControllers() = 0;
		virtual void updateControllers() = 0;
	};

	class DesktopInput : public Input {
	public:
		virtual std::vector<Joystick*> getControllers() {
			return packedControllers; // TODO: replace with real joystick getter
		}

		virtual void updateControllers() {
			packedControllers.clear();
			for (int i=0; i<GLFW_JOYSTICK_LAST; i++) {
				if (glfwJoystickPresent(i)) {
					if (controllers[i] == nullptr) {
						controllers[i] = new Joystick(i);
					} else {
						controllers[i]->updateMetadata();
					}
					packedControllers.push_back(controllers[i]);
				} else {
					controllers[i] = nullptr;
				}
			}
		}
	private:
		std::array<Joystick*, GLFW_JOYSTICK_LAST> controllers;
		std::vector<Joystick*> packedControllers;
	};

	class NullInput : public Input {
	public:
		virtual std::vector<Joystick*> getControllers() {
			return std::vector<Joystick*>();
		}
		virtual void updateControllers() {}
	};
}