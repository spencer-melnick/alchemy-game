#pragma once

#include "resource.h"
#include "texture.h"

namespace Engine
{

	class ResourceManager {
	public:
		ResourceManager();

		Resource* loadResource(std::string filename, Byte priority);
		Resource* getResource(std::string filename);
		
		void deleteResources(Byte priority);

		template <typename T>
		T* getResource(std::string filename) {
			Resource* resource = getResource(filename);

			if (resource == nullptr)
				return nullptr;

			T* typed;
			try {
				typed = dynamic_cast<T*>(resource);
			}
			catch (std::bad_cast& error) {
				Log(filename + " was unable to be cast to requested type + \"" + error.what() + "\"", LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
				return nullptr;
			}

			return typed;
		};


		std::vector < std::pair<std::string, ResourceFactory*> > extensionAssociations;

	protected:
		Resource* getResource(Hash id);

	private:
		ResourceMap resources_;
		std::hash<std::string> hash_;

	};

}
