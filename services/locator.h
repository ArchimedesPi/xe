#pragma once

#include "services/input.h"
#include "services/resources.h"

namespace services {
	class Locator {
	public:
		static void initialize() {
            input_service_ = &null_input_service_;
            resource_locator_ = &null_resource_locator_;
        }
		
		static Input& getInput() { return *input_service_; }

        static ResourceLocator& resource() { return *resource_locator_; }

		static void provideInput(services::Input *service) {
			if (service == NULL)
				input_service_ = &null_input_service_;
			else
				input_service_ = service;
		}

        static void provideResourceLocator(services::ResourceLocator *service) {
            if (service == NULL)
                resource_locator_ = &null_resource_locator_;
            else
                resource_locator_ = service;
        }

	private:
		static Input *input_service_;
		static NullInput null_input_service_;

        static ResourceLocator *resource_locator_;
        static NullResourceLocator null_resource_locator_;
	};
}
