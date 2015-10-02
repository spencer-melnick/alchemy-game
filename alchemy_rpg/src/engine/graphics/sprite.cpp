#include "sprite.h"

using namespace Engine;

Transform::Transform() :
	position(Vector2D(0.0, 0.0)), depth(0)
{};

Sprite::Sprite(std::function<void()> depthCallback) :
	depthCallback_(depthCallback)
{};

bool Sprite::operator<(const Sprite& x) const {
	return (transform_.depth > x.transform_.depth);
}

void Sprite::setSize(Vector2D size) {
	size_ = size;
}

void Sprite::setSource(SDL_Rect source) {
	source_ = source;
}

void Sprite::setTexture(SDL_Texture* texture) {
	texture_ = texture;
}

void Sprite::setTransform(Transform transform) {
	transform_ = transform;
	depthCallback_();
}

Vector2D Sprite::getSize() {
	return size_;
}

SDL_Rect Sprite::getSource() {
	return source_;
}

SDL_Texture* Sprite::getTexture() {
	return texture_;
}

Transform Sprite::getTransform() {
	return transform_;
}
