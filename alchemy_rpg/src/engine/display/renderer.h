#pragma once

#include <SDL.h>

#include "window.h"

namespace Engine {

	class Renderer {
	public:
		Renderer(Window& window);

		void create(Uint32 flags);
		SDL_Renderer* getSdlRenderer() const;


	private:
		Window& window_;
		SDL_Renderer* sdlRenderer_;
		Uint32 lastFlags_;
		
		void destroyRenderer();
		void createRenderer(Uint32 flags);
	};
}
