#pragma once

#include <fstream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "resource.h"
#include "../core/linkedResource.h"
#include "../display/renderer.h"

namespace Engine
{

	class Texture;

	class TextureFactory {
	public:
		TextureFactory(Renderer& renderer, ResourceMap& resources, std::hash<std::string>& hash);

		Texture* loadFromFile(std::string filename);

	private:
		Renderer& renderer_;
		ResourceMap& resources_;
		std::ifstream fileStream_;
		std::hash<std::string>& hash_;
	};

	class Texture : public Resource, protected LinkedResource {
		friend class TextureFactory;
	public:
		Texture(std::string filename, const Renderer& renderer);
		virtual ~Texture() override;

		SDL_Texture* getTexture();
		size_t getSize();
		virtual ResourceType getType() override;

	protected:
		std::shared_ptr<std::vector<char> > rawData_;
		size_t dataSize_;
		SDL_Texture* texture_;
		const Renderer& renderer_;

		void loadTexture();
		void deleteTexture();

		virtual void onDestroy() override;
		virtual void onRecreate() override;
	};
}
