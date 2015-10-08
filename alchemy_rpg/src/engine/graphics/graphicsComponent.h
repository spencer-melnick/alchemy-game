#pragma once

#include <vector>

#include <SDL.h>

#include "../entity/component.h"
#include "../entity/message.h"
#include "../file/texture.h"
#include "../math/math.h"

#include "spriteRenderer.h"

namespace Engine
{

	class GraphicsComponent: public Component<GraphicsComponent> {
	public:
		GraphicsComponent(Entity& owner, SpriteRenderer& renderer);
		virtual ~GraphicsComponent();

	protected:
		SpriteRenderer& renderer_;
		std::vector<Sprite*> ownedSprites_;

		Sprite* createNewSprite();
	};
}

