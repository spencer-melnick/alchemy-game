#include "textureFactory.h"

TextureSheet::TextureSheet(SDL_Texture* texture, std::string filename, SheetConfig config)
	: Texture(texture, filename)
{
	unsigned char framesX = static_cast<unsigned char>(std::floor((config.imageWidth - (config.paddingX * 2))
		/ (config.tileWidth + config.spaceX)));
	unsigned char framesY = static_cast<unsigned char>(std::floor((config.imageHeight - (config.paddingY * 2))
		/ (config.tileHeight + config.spaceY)));

	for (unsigned char i = 0; i < framesX; i++) {
		frames_[i] = std::vector<SDL_Rect>();
		for (unsigned char j = 0; j < framesY; j++) {
			frames_[i][j] = SDL_Rect();
			frames_[i][j].x = config.paddingX + ((config.tileWidth + config.spaceX) * static_cast<unsigned int>(i));
			frames_[i][j].y = config.paddingY + ((config.tileHeight + config.spaceY) * static_cast<unsigned int>(j));
			frames_[i][j].w = config.tileWidth;
			frames_[i][j].h = config.tileHeight;
		}
	}
}

Texture* TextureFactory::loadTexture(std::string filename, std::ostream& log,
	TextureSheet::SheetConfig* config)
{
	auto i = textures_.begin();

	for (i; i != textures_.end(); i++) {
		if (i->filename_ == filename)
			break;
	}

	if (i != textures_.end())
		return &(*i);

	SDL_Texture* texture = loadTextureData(filename, log);
	if (texture == nullptr)
		return nullptr;

	if (config == nullptr)
		textures_.push_front(Texture(texture, filename));
	else
		textures_.push_front(TextureSheet(texture, filename, *config));

	return &(textures_.front());
}

void TextureFactory::unloadTextures() {
	for (auto i = textures_.begin(); i != textures_.end(); i++) {
		SDL_DestroyTexture(i->texture_);
	}

	textures_.clear();
}

void TextureFactory::reloadTextures(std::ostream& log) {
	for (auto i : textures_) {
		SDL_Texture* texture = loadTextureData(i.filename_, log);
		if (texture == nullptr)
			log << "Image reload failed!\n" << i.filename_ << " no longer references a valid texture\n";
		i.texture_ = texture;
	}
}

SDL_Texture* TextureFactory::loadTextureData(std::string filename, std::ostream& log) {
	loadingSurface_ = IMG_Load(filename.c_str());
	if (!loadingSurface_) {
		log << "Image failed to load: " << filename << '\n';
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, loadingSurface_);
	SDL_FreeSurface(loadingSurface_);

	log << filename << " loaded successfully\n";

	return texture;
}
