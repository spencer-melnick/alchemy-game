#include "resource.h"

using namespace Engine;

Resource::Resource(std::string filename)
	: filename_(filename) {
	id_ = hashFunction(filename);
}

Hash Resource::getId() {
	return id_;
}

std::string Resource::getFilename() {
	return filename_;
}
