#include "textureFactory.h"

SDL_Texture* TextureFactory::loadTexture(std::string filename, std::ostream& log) {
	auto i = textures_.begin();

	for (i; i != textures_.end(); i++) {
		if (i->filename_ == filename)
			break;
	}

	if (i != textures_.end())
		return i->texture_;

	loadingSurface_ = IMG_Load(filename.c_str());
	if (!loadingSurface_) {
		log << "Image failed to load: " << filename << '\n';
		return NULL;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, loadingSurface_);
	textures_.push_front({ filename, texture });
	SDL_FreeSurface(loadingSurface_);

	log << filename << " loaded successfully\n";

	return texture;
}

void TextureFactory::unloadTextures() {
	for (auto i = textures_.begin(); i != textures_.end(); i++) {
		SDL_DestroyTexture(i->texture_);
	}

	textures_.clear();
}
