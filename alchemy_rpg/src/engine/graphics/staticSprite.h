#pragma once

#include "graphicsComponent.h"

namespace Engine {

	class SetTextureMessage : public Message<SetTextureMessage> {
	public:
		SetTextureMessage(Texture* t);

		Texture* texture;
	};

	class StaticSpriteComponent : public GraphicsComponent {
	public:
		StaticSpriteComponent(Entity& owner, SpriteRenderer& renderer, Texture* texture);
		void setTexture(Texture* texture);
		virtual void receiveMessage(BaseMessage& message) override;

	protected:
		Texture* texture_;
		Sprite* sprite_;
	};

}
