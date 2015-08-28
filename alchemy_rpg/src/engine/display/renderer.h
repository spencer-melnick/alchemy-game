#pragma once

#include <SDL.h>

#include "window.h"

namespace Engine {

	class Renderer : public LinkedResource {
	public:
		Renderer(Window& window);

		void create(Uint32 flags);
		SDL_Renderer* getSdlRenderer() const;

	protected:
		virtual void onDestroy() override;
		virtual void onRecreate() override;

	private:
		Window& window_;
		SDL_Renderer* sdlRenderer_;
		Uint32 lastFlags_;
		
		void destroyRenderer();
		void createRenderer(Uint32 flags);
	};
}
