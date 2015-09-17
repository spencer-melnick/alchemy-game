#include "resource.h"

using namespace Engine;

Resource::Resource(std::string filename, Byte priority)
	: filename_(filename), priority_(priority) {
	id_ = hashFunction(filename);
}

Hash Resource::getId() {
	return id_;
}

std::string Resource::getFilename() {
	return filename_;
}

Byte Resource::getPriority() {
	return priority_;
}
