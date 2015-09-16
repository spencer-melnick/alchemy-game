#pragma once

#include "graphicsComponent.h"

namespace Engine
{

	class Sprite : public GraphicsComponent {
	public:
		Sprite(Texture* texture, Entity& owner);

		virtual Texture* getTexture() override;
		virtual SDL_Rect* getSourceRect() override;
		virtual void update() override;

		virtual void setTexture(Texture* texture);

	protected:
		Texture* texture_;
	};

}
