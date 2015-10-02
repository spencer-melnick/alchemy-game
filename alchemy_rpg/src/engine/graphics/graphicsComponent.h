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
	};

}

