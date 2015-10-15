#pragma once

#include <SDL.h>

#include "graphicsComponent.h"

namespace Engine {

	class SetTextureMessage : public Message<SetTextureMessage> {
	public:
		SetTextureMessage(Texture* t);

		Texture* texture;
	};

	class SetSpriteSourceMessage : public Message<SetSpriteSourceMessage> {
	public:
		SetSpriteSourceMessage(SDL_Rect s);

		SDL_Rect source;
	};

	class StaticSpriteComponent : public GraphicsComponent {
	public:
		StaticSpriteComponent(Entity& owner, SharedSprite sprite, Texture* texture);
		void setTexture(Texture* texture);
		virtual void receiveMessage(BaseMessage& message) override;

	protected:
		Texture* texture_;
		SharedSprite sprite_;
	};

}
