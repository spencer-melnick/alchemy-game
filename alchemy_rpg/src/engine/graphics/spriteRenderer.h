#pragma once

#include <vector>
#include <algorithm>
#include <memory>

#include "../display/renderer.h"
#include "sprite.h"

namespace Engine
{
	using SharedSprite = std::shared_ptr<Sprite>;
	using WeakSprite = std::weak_ptr<Sprite>;

	class GraphicsComponent;

	class SpriteRenderer {
		friend class GraphicsComponent;
	public:
		SpriteRenderer(Renderer& renderer);
		void sort();
		void render();
		SharedSprite newSprite();

		size_t getNumSprites();

	protected:
		class SpriteWrapper {
		public:
			Sprite data;
			std::vector<WeakSprite>& owner;
			std::vector<WeakSprite>::iterator itr;

			SpriteWrapper(std::vector<WeakSprite>& s, std::function<void()> depthCallback);
			~SpriteWrapper();
		};

		bool sorted_;
		std::vector<WeakSprite> sprites_;
		Renderer& renderer_;
		std::function<void()> depthCallback_;
	};

}
