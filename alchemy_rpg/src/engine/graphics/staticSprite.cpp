#include "staticSprite.h"

using namespace Engine;

SetTextureMessage::SetTextureMessage(Texture* t)
	: texture(t)
{}

SetSpriteSourceMessage::SetSpriteSourceMessage(SDL_Rect s)
	: source(s)
{}

StaticSpriteComponent::StaticSpriteComponent(Entity& owner, SpriteRenderer& renderer, Texture* texture)
	: GraphicsComponent(owner, renderer), texture_(texture) {
	sprite_ = createNewSprite();
	sprite_->setTexture(texture_->getTexture());

	Vector2D dim = texture->getSize();

	SDL_Rect src;
	src.w = static_cast<int>(dim.x);
	src.h = static_cast<int>(dim.y);
	src.x = 0;
	src.y = 0;

	sprite_->setSource(src);
	sprite_->setPosition(dim/2.0);
	sprite_->setSize(dim);
}

void StaticSpriteComponent::setTexture(Texture* texture) {
	texture_ = texture;
	sprite_->setTexture(texture_->getTexture());
}

void StaticSpriteComponent::receiveMessage(BaseMessage& message) {
	if (message.isA(SetTextureMessage::getStaticId()))
	{
		SetTextureMessage& setMessage = static_cast<SetTextureMessage&>(message);
		setTexture(setMessage.texture);
	}

	if (message.isA(SetSpriteSourceMessage::getStaticId()))
	{
		SetSpriteSourceMessage& setMessage = static_cast<SetSpriteSourceMessage&>(message);
		sprite_->setSource(setMessage.source);
	}
}
