#include "manager.h"

using namespace Engine;

ResourceManager::ResourceManager()
	{}

Resource* ResourceManager::loadResource(std::string filename, Byte priority) {
	Hash id = hash_(filename);

	Resource* prior = getResource(id);
	if (prior != nullptr) {
		Log("Attempted to load " + filename + ", but it already exists in memory", LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
		return prior;
	}

	std::string fileExtension = filename.substr(filename.find_last_of('.'));

	for (auto i : extensionAssociations) {
		if (i.first.find(fileExtension + " ") != std::string::npos) {
			Resource* resource = i.second->loadResource(filename, priority);
			if (resource == nullptr) {
				Log(filename + " was not created successfully", LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
				return nullptr;
			}

			resources_[id] = resource;
			return resources_[id];
		}
	}

	Log(fileExtension + " is not a valid extension for " + filename, LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
	return nullptr;
}

Resource* ResourceManager::getResource(std::string filename) {
	Hash id = hash_(filename);

	return getResource(id);
}

Resource* ResourceManager::getResource(Hash id) {
	auto i = resources_.find(id);
	if (i != resources_.end())
		return i->second;

	return nullptr;
}

void ResourceManager::deleteResources(Byte priority) {
	std::vector<ResourceMap::iterator> removed;
	
	for (auto i = resources_.begin(); i != resources_.end(); i++)
		if (i->second->getPriority() >= priority)
			removed.push_back(i);

	for (auto i : removed) {
		delete i->second;
		resources_.erase(i);
	}
}
