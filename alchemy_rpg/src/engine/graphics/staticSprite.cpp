#include "staticSprite.h"

using namespace Engine;

SetTextureMessage::SetTextureMessage(Texture* t)
	: texture(t)
{}

StaticSpriteComponent::StaticSpriteComponent(Entity& owner, SpriteRenderer& renderer, Texture* texture)
	: GraphicsComponent(owner, renderer), texture_(texture) {
	sprite_ = createNewSprite();
	sprite_->setTexture(texture_->getTexture());

	SDL_Rect src;
	src.w = 128;
	src.h = 128;
	src.x = 0;
	src.y = 0;

	sprite_->setSource(src);
	sprite_->setPosition(Vector2D(128.0, 128.0));
	sprite_->setSize(Vector2D(128.0, 128.0));
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
}
