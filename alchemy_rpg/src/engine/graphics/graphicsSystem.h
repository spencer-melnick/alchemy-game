#pragma once

#include "../display/renderer.h"
#include "../entity/entity.h"

namespace Engine {

	class GraphicsSystem {
	public:
		GraphicsSystem(Renderer& renderer);

		void render(Entity& scene);

	protected:
		Renderer& renderer_;
	};

}
