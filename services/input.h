#pragma once

#include <string>
#include <vector>
#include <array>

#include <GLFW/glfw3.h>

class Controller {
public:
	Controller(int idx) : index(idx), enabled(false) {this->updateMetadata();}

    double getAxis(std::string axis);
    double getButton(std::string button);

	void updateMetadata();
	std::string dump();

	int index;
	std::string name;
	bool enabled;
};

namespace services {
	class Input {
	public:
		virtual std::vector<Controller*> getControllers() = 0;
		virtual void updateControllers() = 0;
	};

	class DesktopInput : public Input {
	public:
		virtual std::vector<Controller*> getControllers() {
			return packedControllers;
		}

		virtual void updateControllers() {
			packedControllers.clear();
			for (int i=0; i<GLFW_JOYSTICK_LAST; i++) {
				if (glfwJoystickPresent(i)) {
					if (controllers[i] == nullptr) {
						controllers[i] = new Controller(i);
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
		std::array<Controller*, GLFW_JOYSTICK_LAST> controllers;
		std::vector<Controller*> packedControllers;
	};

	class NullInput : public Input {
	public:
		virtual std::vector<Controller*> getControllers() {
			return std::vector<Controller*>();
		}
		virtual void updateControllers() {}
	};
}
