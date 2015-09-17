#include "renderer.h"

using namespace Engine;

Renderer::Renderer(Window& window) :
	window_(window), sdlRenderer_(nullptr) {
}

void Renderer::create(Uint32 flags) {
	lastFlags_ = flags;

	if (sdlRenderer_ != nullptr)
		destroyRenderer();
	
	createRenderer(flags);
}

SDL_Renderer* Renderer::getSdlRenderer() const {
	return sdlRenderer_;
}

void Renderer::destroyRenderer() {
	if (sdlRenderer_ != nullptr) {
		SDL_DestroyRenderer(sdlRenderer_);
		sdlRenderer_ = nullptr;
	}
}

void Renderer::createRenderer(Uint32 flags) {
	sdlRenderer_ = SDL_CreateRenderer(window_.sdlWindow_, -1, flags);

	if (sdlRenderer_ == nullptr)
		throw Engine::Error(SystemName::SYSTEM_DISPLAY, true, "Failed to create a renderer: " + SdlStringError());
}
