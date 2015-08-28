#include "manager.h"

using namespace Engine;

ResourceManager::ResourceManager(Renderer& renderer)
	: renderer_(renderer), textureFactory_(renderer, resources_, hash_) {}

Resource& ResourceManager::getResource(std::string filename) {
	Hash id = hash_(filename);

	auto i = resources_.find(id);
	if (i != resources_.end())
		return *(i->second);

	std::string fileExtension = filename.substr(filename.find_last_of('.'));

	if (imageExtensions_.find(fileExtension + " ") != std::string::npos) {
		Texture* texture = textureFactory_.loadFromFile(filename);
		if (texture == nullptr)
			throw Engine::Error(SystemName::SYSTEM_FILE, true, filename + " already exists, but is unable to be accessed (this error shouldn't be possible)");

		return *texture;
	}

	throw Engine::Error(SystemName::SYSTEM_FILE, false, fileExtension + " is not a valid extension for " + filename);
}

void ResourceManager::deleteResources() {
	resources_.clear();
}

const std::string ResourceManager::imageExtensions_ = ".png .jpg .jpeg";
