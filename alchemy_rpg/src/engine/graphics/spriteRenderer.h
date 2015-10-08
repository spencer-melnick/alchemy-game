#pragma once

#include <vector>
#include <algorithm>

#include "../display/renderer.h"
#include "sprite.h"

namespace Engine
{
	class GraphicsComponent;

	class SpriteRenderer {
		friend class GraphicsComponent;
	public:
		SpriteRenderer(Renderer& renderer);
		void sort();
		void render();
		void removeSprite(Sprite* sprite);

	protected:
		bool sorted_;
		std::vector<Sprite> sprites_;
		Renderer& renderer_;
		std::function<void()> depthCallback_;

		Sprite* newSprite();
	};

}
