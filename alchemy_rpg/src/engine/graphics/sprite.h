#pragma once

#include "graphicsComponent.h"

namespace Engine
{
	struct Transform {
		Vector2D position_;
		Vector2D size_;
		double depth_;
	};

	class Sprite {
	public:

	protected:
		SDL_Texture* texture;
		SDL_Rect source;
		Vector2D size;
	};

}
