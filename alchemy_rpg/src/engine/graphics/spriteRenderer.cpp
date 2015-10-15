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
		std::rotate(std::upper_bound(sprites_.begin(), i, *i, 
			[](const WeakSprite a, const WeakSprite b) {
				if (a.expired() || b.expired())
					throw Engine::Error(SystemName::SYSTEM_GRAPHICS, true, "SpriteRenderer contained an invalid sprite");
				return *(a.lock()) < *(b.lock()); }),
		i, i + 1);
	}
}

void SpriteRenderer::render() {
	for (auto i : sprites_) {
		SDL_Rect dest;
		auto sprite = *(i.lock());

		dest.w = static_cast<int>(sprite.size_.x);
		dest.h = static_cast<int>(sprite.size_.y);
		dest.x = static_cast<int>(sprite.transform_.position.x) - static_cast<int>(sprite.size_.x / 2);
		dest.y = static_cast<int>(sprite.transform_.position.y) - static_cast<int>(sprite.size_.y / 2);

		SDL_RenderCopy(renderer_.getSdlRenderer(), sprite.texture_, &sprite.source_, &dest);
	}
}

SpriteRenderer::SpriteWrapper::SpriteWrapper(std::vector<WeakSprite> &s, std::function<void()> depthCallback) :
	owner(s), data(depthCallback) {};

SpriteRenderer::SpriteWrapper::~SpriteWrapper() {
	owner.erase(itr);
}

SharedSprite SpriteRenderer::newSprite() {
	auto intern = std::make_shared<SpriteRenderer::SpriteWrapper>(sprites_, depthCallback_);
	SharedSprite alias = SharedSprite(intern, &(intern->data));

	sprites_.push_back(WeakSprite(alias));
	auto itr = sprites_.end();
	itr--;
	intern->itr = itr;
	return alias;
}

size_t SpriteRenderer::getNumSprites() {
	return sprites_.size();
}
