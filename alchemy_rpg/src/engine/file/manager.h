#pragma once

#include "resource.h"
#include "texture.h"

namespace Engine
{

	class ResourceManager {
	public:
		ResourceManager(Renderer& renderer);

		Resource& getResource(std::string filename);
		void deleteResources();

	private:
		ResourceMap resources_;
		Renderer& renderer_;
		std::hash<std::string> hash_;

		TextureFactory textureFactory_;

		static const std::string imageExtensions_;

	};

}
