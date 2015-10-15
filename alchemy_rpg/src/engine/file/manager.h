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
		T* getResource(std::string filename);


		std::vector < std::pair<std::string, ResourceFactory*> > extensionAssociations;

	protected:
		Resource* getResource(Hash id);

	private:
		ResourceMap resources_;
		std::hash<std::string> hash_;

	};

}
