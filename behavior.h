#pragma once

class Behavior {
public:
	// -- events
	// The respective subsystems should call these on every behavior

	// management events
	virtual void runOnStart() = 0;
	virtual void runOnDestroy() = 0;
	virtual void runOnEnable() = 0;
	virtual void runOnDisable() = 0;

	// update variants
	virtual void onUpdate() = 0;
	virtual void onUpdatePhysics() = 0;
	virtual void onUpdatePostCalculation() = 0;
};

