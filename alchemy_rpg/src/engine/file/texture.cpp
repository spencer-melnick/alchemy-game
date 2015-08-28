#include "texture.h"

using namespace Engine;

TextureFactory::TextureFactory(Renderer& renderer, ResourceMap& resources, std::hash<std::string>& hash)
	: renderer_(renderer), resources_(resources), hash_(hash) {}

Texture* TextureFactory::loadFromFile(std::string filename) {
	Hash id = hash_(filename);

	if (resources_.find(id) != resources_.end())
		return nullptr;

	fileStream_.open(filename, std::ios::binary);

	if (!fileStream_.is_open())
		throw Engine::Error(SystemName::SYSTEM_FILE, false, filename + " was unable to be opened");

	Texture* texture = static_cast<Texture*>(resources_.emplace(id, std::make_unique<Texture>(Texture(filename, renderer_))).first->second.get());
	renderer_.linkResource(texture);

	fileStream_.seekg(0, std::ios::end);
	size_t fileSize = static_cast<size_t>(fileStream_.tellg());
	fileStream_.seekg(0, std::ios::beg);

	texture->dataSize_ = fileSize;
	texture->rawData_.swap(std::make_shared<std::vector<char> >(fileSize));

	fileStream_.read(texture->rawData_->data(), fileSize);
	texture->loadTexture();

	return texture;
}

Texture::Texture(std::string filename, const Renderer& renderer)
	: Resource(filename), texture_(nullptr), renderer_(renderer) {}

Texture::~Texture() {
	deleteTexture();
}

SDL_Texture* Texture::getTexture() {
	return texture_;
}

ResourceType Texture::getType() {
	return ResourceType::RESOURCE_TEXTURE;
}

size_t Texture::getSize() {
	return dataSize_;
}

void Texture::loadTexture() {
	texture_ = IMG_LoadTexture_RW(renderer_.getSdlRenderer(), SDL_RWFromMem(rawData_->data(), dataSize_), 0);
	if (texture_ == nullptr)
		throw Engine::Error(SystemName::SYSTEM_FILE, false, getFilename() + " could not be loaded into texture memory " + std::string(IMG_GetError()));
}

void Texture::deleteTexture() {
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}

void Texture::onDestroy() {
	deleteTexture();
}

void Texture::onRecreate() {
	loadTexture();
}
