#pragma once

#include <functional>

#include <SDL.h>

#include "../math/vector2d.h"

namespace Engine
{
	class SpriteRenderer;

	struct Transform {
		Transform();

		Vector2D position;
		double depth;
	};

	class Sprite {
		friend class SpriteRenderer;
	public:
		void setTexture(SDL_Texture* texture);
		void setSource(SDL_Rect source);
		void setSize(Vector2D size);
		void setTransform(Transform transform);
		void setDepth(double depth);
		void setPosition(Vector2D position);

		SDL_Texture* getTexture();
		SDL_Rect getSource();
		Vector2D getSize();
		Transform getTransform();

		bool operator<(const Sprite& x) const;

	protected:
		Sprite(std::function<void()> depthCallback);

		SDL_Texture* texture_;
		SDL_Rect source_;
		Vector2D size_;
		Transform transform_;
		std::function<void()> depthCallback_;
	};

}
