#pragma once

#include <vector>
#include <algorithm>

#include "sprite.h"

namespace Engine
{

	class SpriteRenderer {
	public:
		SpriteRenderer(Renderer& renderer);
		void sort();
		void render();
		void removeSprite(Sprite* sprite);
		Sprite* newSprite();

	protected:
		bool sorted_;
		std::vector<Sprite> sprites_;
		Renderer& renderer_;
		std::function<void()> depthCallback_;
	};

}
