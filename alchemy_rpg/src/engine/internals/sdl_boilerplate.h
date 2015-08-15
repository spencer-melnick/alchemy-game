#ifndef engine_internals_sdl_boilerplate_h
#define engine_internals_sdl_boilerplate_h

#include <iostream>
#include <stdexcept>
#include <forward_list>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include <tinyxml2.h>

#include "vector2d.h"

#define IMAGE_TYPES (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)


struct SdlApplicationData {
	struct DisplayMode {
		int w;
		int h;
	};

	class WindowConfig {
	public:
		std::ostream* log;

		WindowConfig(SdlApplicationData* data, tinyxml2::XMLDocument* config);
		~WindowConfig();

		void saveConfig();
		void updateResolutions();

		void setVsync(bool vsync); //does not apply until restart
		void setFullscreen(bool fullscreen);
		bool getVsync();
		bool getFullscreen();
		DisplayMode getResolution();

	private:
		bool vsync_;
		bool fullscreen_;
		DisplayMode mode_;

		SdlApplicationData* data_;
		tinyxml2::XMLDocument* config_;
		std::vector<DisplayMode> modes_;
	};

	SDL_Window* window;
	SDL_Renderer* renderer;
	WindowConfig* config;
};

SdlApplicationData* initializeSdl(std::ostream& log);
void closeSdl(SdlApplicationData* applicationData);

#endif