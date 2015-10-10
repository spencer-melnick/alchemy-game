#include "texture.h"

using namespace Engine;

TextureFactory::TextureFactory(Renderer& renderer)
	: renderer_(renderer) {}

Resource* TextureFactory::loadResource(std::string filename, Byte priority) {
	SDL_Surface* temp = IMG_Load(filename.c_str());

	if (temp == nullptr)
	{
		Log(filename + " was unable to be opened", LogLevel::LOG_WARNING, SystemName::SYSTEM_FILE);
		return nullptr;
	}

	SDL_Texture* raw = SDL_CreateTextureFromSurface(renderer_.getSdlRenderer(), temp);
	Vector2D dim(temp->w, temp->h);
	Resource* texture = new Texture(filename, priority, raw, dim);

	SDL_FreeSurface(temp);

	return texture;
}

Texture::Texture(std::string filename, Byte priority, SDL_Texture* texture, Vector2D size)
	: Resource(filename, priority), texture_(texture), size_(size) {}

Texture::~Texture() {
	deleteTexture();
}

SDL_Texture* Texture::getTexture() {
	return texture_;
}

Vector2D Texture::getSize() {
	return size_;
}

ResourceType Texture::getType() {
	return ResourceType::RESOURCE_TEXTURE;
}

void Texture::deleteTexture() {
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}
