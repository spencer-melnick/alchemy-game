#pragma once

#include <fstream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include"../math/vector2d.h"
#include "resource.h"
#include "../display/renderer.h"


#define IMAGE_EXTENSIONS ".png .jpg .jpeg"

namespace Engine
{

	class Texture;

	class TextureFactory: public ResourceFactory {
	public:
		TextureFactory(Renderer& renderer);

		virtual Resource* loadResource(std::string filename, Byte priority) override;

	private:
		Renderer& renderer_;
	};

	class Texture : public Resource {
		friend class TextureFactory;
	public:
		virtual ~Texture() override;

		SDL_Texture* getTexture();
		Vector2D getSize();
		virtual ResourceType getType() override;

	protected:
		SDL_Texture* texture_;
		std::string name_;
		Vector2D size_;

		Texture(std::string filename, Byte priority, SDL_Texture* data, Vector2D size);

		void deleteTexture();
	};
}
