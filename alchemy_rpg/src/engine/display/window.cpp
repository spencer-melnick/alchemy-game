#include "window.h"

using namespace Engine;

Window::Window()
	: sdlWindow_(nullptr) {}

void Window::create(std::string name, int x, int y, int width, int height, Uint32 flags) {
	initializeSdlVideo();

	if (sdlWindow_ != nullptr)
		destroy();

	sdlWindow_ = SDL_CreateWindow(name.c_str(), x, y, width, height, flags);

	if (sdlWindow_ == nullptr)
		throw Engine::Error(SystemName::SYSTEM_DISPLAY, true, "Failed to create window: " + SdlStringError());
}

void Window::initializeSdlVideo() {
	if (SDL_WasInit(SDL_INIT_VIDEO))
		return;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw Engine::Error(SystemName::SYSTEM_DISPLAY, true, "Failed to initialize SDL_Video: " + SdlStringError());
}
