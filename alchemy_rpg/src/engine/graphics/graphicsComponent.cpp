#include "graphicsComponent.h"

using namespace Engine;

GraphicsComponent::GraphicsComponent(Entity & owner, SpriteRenderer& renderer)
	: Component(owner), renderer_(renderer) {}

GraphicsComponent::~GraphicsComponent() {
	for (auto i : ownedSprites_)
		renderer_.removeSprite(i);
}

Sprite* GraphicsComponent::createNewSprite() {
	Sprite* sprite = renderer_.newSprite();
	ownedSprites_.push_back(sprite);
	return ownedSprites_.back();
}
