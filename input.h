#pragma once

#include <string>
#include <vector>

class Joystick {
public:
	Joystick(int idx) : index(idx) {this->updateMetadata();}

	void updateMetadata();

	std::string dump();

	int index;
	std::string name;
};

class Input {
public:
	static std::vector<Joystick> getJoysticks();
};