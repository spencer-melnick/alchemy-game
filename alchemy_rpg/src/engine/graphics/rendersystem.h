#ifndef engine_graphics_rendersystem_h
#define engine_graphics_rendersystem_h

#include <forward_list>
#include <list>
#include <memory>

#include <SDL.h>

#include "rendercomponent.h"

class RenderSystem {
public:
	struct State {
		Transform transform;
	};

	RenderSystem() {
		statestack_.push_front(State());
	}

	SharedRenderComponent registerComponent(SharedRenderComponent component);
	void unregisterComponent(const SharedRenderComponent& component);

	void render(SDL_Renderer* renderer);

protected:
	void render(SDL_Renderer* renderer, const SharedRenderComponent& component);

private:
	SDL_Rect rect_;

	std::list<SharedRenderComponent > components_;
	std::forward_list<State> statestack_;
};

#endif