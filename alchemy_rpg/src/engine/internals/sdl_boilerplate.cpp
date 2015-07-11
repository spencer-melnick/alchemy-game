#include "sdl_boilerplate.h"

SdlApplicationData initializeSdl(std::ostream& log) {
	SdlApplicationData applicationData;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		log << "SDL_Init Error: " << SDL_GetError() << '\n';

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initialization failure", "Check the error log for more details", NULL);
		throw std::runtime_error("SDL initialization failure");
	}

	applicationData.window = SDL_CreateWindow("sdl_window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if (applicationData.window == nullptr) {
		log << "SDL_CreateWindow Error: " << SDL_GetError() << '\n';

		SDL_Quit();

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initialization failure", "Check the error log for more details", NULL);
		throw std::runtime_error("SDL initialization failure");
	}

	applicationData.renderer = SDL_CreateRenderer(applicationData.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (applicationData.renderer == nullptr) {
		log << "SDL_CreateRenderer Error: " << SDL_GetError() << '\n';

		SDL_DestroyWindow(applicationData.window);
		SDL_Quit();

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initialization failure", "Check the error log for more details", applicationData.window);
		throw std::runtime_error("SDL initialization failure");
	}

	log << "SDL initialized properly" << '\n';



	if (IMG_Init(IMAGE_TYPES) != IMAGE_TYPES) { // IMG_Init returns the flags for successfully initalized image libraries
		log << "SDL_IMG_Init Error : " << IMG_GetError() << '\n';
		IMG_Quit();

		SDL_DestroyRenderer(applicationData.renderer);
		SDL_DestroyWindow(applicationData.window);
		SDL_Quit();

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initialization failure", "Check the error log for more details", applicationData.window);
		throw std::runtime_error("SDL initialization failure");
	}

	log << "SDL_Image initialized properly" << '\n';


	return applicationData;
}

void closeSdl(SdlApplicationData applicationData) {
	IMG_Quit();
	SDL_DestroyRenderer(applicationData.renderer);
	SDL_DestroyWindow(applicationData.window);
	SDL_Quit();
}
