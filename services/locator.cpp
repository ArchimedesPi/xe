#include "locator.h"

using namespace services;
Input *Locator::input_service_;
NullInput Locator::null_input_service_;

ResourceLocator *Locator::resource_locator_;
NullResourceLocator Locator::null_resource_locator_;
