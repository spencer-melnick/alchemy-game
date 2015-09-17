#pragma once

#include <string>
#include <list>

#include <SDL.h>

#include "../core/core.h"

namespace Engine {

	class Window : public LinkedResource {
		friend class Renderer;

	public:
		Window();

		void create(std::string name, int x, int y, int width, int height, Uint32 flags);
		void initializeSdlVideo();

	protected:
		SDL_Window* sdlWindow_;
	};

}
