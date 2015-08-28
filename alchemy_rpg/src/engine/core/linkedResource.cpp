#include "linkedResource.h"

using namespace Engine;

void LinkedResource::destroy() {
	for (auto i : resources_) {
		if (i != nullptr) {
			i->destroy();
		}
	}
	resources_.clear();

	onDestroy();
}

void LinkedResource::recreate() {
	onRecreate();

	for (auto i : resources_)
		i->recreate();
}

void LinkedResource::linkResource(LinkedResource* resource) {
	if (resource != nullptr) {
		resources_.push_back(resource);
		resources_.unique();
	}
}

void LinkedResource::unlinkResource(LinkedResource* resource) {
	resources_.remove(resource);
}
