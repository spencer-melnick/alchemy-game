#include "sprite.h"

using namespace Engine;

Sprite::Sprite(Texture* texture, Entity& owner)
	: texture_(texture), GraphicsComponent(owner) {}

Texture* Sprite::getTexture() {
	return texture_;
}

SDL_Rect* Sprite::getSourceRect() {
	return nullptr;
}

void Sprite::update() {
}

void Sprite::setTexture(Texture* texture) {
	texture_ = texture;
}
