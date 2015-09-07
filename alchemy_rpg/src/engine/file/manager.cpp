#include "manager.h"

using namespace Engine;

ResourceManager::ResourceManager(Renderer& renderer)
	: renderer_(renderer), textureFactory_(renderer, resources_, hash_) {}

Resource* ResourceManager::getResource(std::string filename) {
	Hash id = hash_(filename);

	auto i = resources_.find(id);
	if (i != resources_.end())
		return (i->second).get();

	std::string fileExtension = filename.substr(filename.find_last_of('.'));

	if (imageExtensions_.find(fileExtension + " ") != std::string::npos) {
		Texture* texture = textureFactory_.loadFromFile(filename);
		if (texture == nullptr)
			Log(filename + " was unable to be accessed by resource manager", LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);

		return texture;
	}

	Log(fileExtension + " is not a valid extension for " + filename, LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
	return nullptr;
}

void ResourceManager::deleteResources() {
	resources_.clear();
}

const std::string ResourceManager::imageExtensions_ = ".png .jpg .jpeg";
