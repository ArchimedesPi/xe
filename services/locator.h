#pragma once

#include "services/input.h"

namespace services {
	class Locator {
	public:
		static void initialize() { input_service_ = &null_input_service_; }
		
		static Input& getInput() { return *input_service_; }

		static void provideInput(services::Input *service) {
			if (service == NULL)
				input_service_ = &null_input_service_;
			else
				input_service_ = service;
		}

	private:
		static Input *input_service_;
		static NullInput null_input_service_;
	};
}