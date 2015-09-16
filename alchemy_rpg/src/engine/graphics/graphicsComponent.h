#pragma once

#include <SDL.h>

#include "../entity/component.h"
#include "../entity/message.h"
#include "../file/texture.h"
#include "../math/math.h"

namespace Engine
{

	class GraphicsComponent: public Component<GraphicsComponent> {
	public:
		GraphicsComponent(Entity& owner);

		virtual void receiveMessage(BaseMessage& message) override;
		virtual Texture* getTexture() = 0;
		virtual SDL_Rect* getSourceRect() = 0;
		virtual void update() = 0;
	};

}

