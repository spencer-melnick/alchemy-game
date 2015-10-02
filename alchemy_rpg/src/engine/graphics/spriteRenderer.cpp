#include "spriteRenderer.h"

using namespace Engine;

SpriteRenderer::SpriteRenderer(Renderer& renderer) :
	renderer_(renderer)
{
	depthCallback_ = std::bind(&SpriteRenderer::sort, this);
};

void SpriteRenderer::sort() {
	//simple STL-powered insertion sort taken from cppreference.com

	for (auto i = sprites_.begin(); i != sprites_.end(); i ++) {
		std::rotate(std::upper_bound(sprites_.begin(), i, *i), i, i + 1);
	}
}

void SpriteRenderer::render() {
	for (auto i : sprites_) {
		SDL_Rect dest;
		dest.w = static_cast<int>(i.size_.x);
		dest.h = static_cast<int>(i.size_.y);
		dest.x = static_cast<int>(i.transform_.position.x) - static_cast<int>(i.size_.x / 2);
		dest.y = static_cast<int>(i.transform_.position.y) - static_cast<int>(i.size_.y / 2);

		SDL_RenderCopy(renderer_.getSdlRenderer(), i.texture_, &i.source_, &dest);
	}
}

void SpriteRenderer::removeSprite(Sprite* sprite) {
	auto x = sprites_.end();

	for (auto i = sprites_.begin(); i != sprites_.end(); i++) {
		if (&(*i) == sprite) {
			x = i;
			break;
		}
	}

	if (x != sprites_.end())
		sprites_.erase(x);
}

Sprite* SpriteRenderer::newSprite() {
	sprites_.push_back(Sprite(depthCallback_));
	return &(sprites_.back());
}
