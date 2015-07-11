#ifndef engine_internals_sdl_boilerplate_h
#define engine_internals_sdl_boilerplate_h

#include <iostream>
#include <stdexcept>

#include <SDL.h>
#include <SDL_image.h>


#define IMAGE_TYPES (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)


struct SdlApplicationData {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

SdlApplicationData initializeSdl(std::ostream& log);
void closeSdl(SdlApplicationData applicationData);

#endif