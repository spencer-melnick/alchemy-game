#ifndef engine_internals_texture_factory_h
#define engine_internals_texture_factory_h

#include <forward_list>
#include <iostream>
#include <string>
#include <stdexcept>

#include <SDL.h>
#include <SDL_image.h>



class TextureFactory {
public:
	TextureFactory(SDL_Renderer* renderer) :
		renderer_(renderer)
	{};

	SDL_Texture* loadTexture(std::string filename, std::ostream& log);
	void unloadTextures();

private:
	struct Texture {
		std::string filename_;
		SDL_Texture* texture_;
	};

	SDL_Renderer* renderer_;
	SDL_Surface* loadingSurface_;
	std::forward_list<Texture> textures_;
};

#endif