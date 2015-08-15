#include "sdl_boilerplate.h"

//TODO: force textures to reload so vsync can be changed during application run

SdlApplicationData* initializeSdl(std::ostream& log) {
	SdlApplicationData* applicationData = new SdlApplicationData();

	tinyxml2::XMLDocument* config = new tinyxml2::XMLDocument;
	config->LoadFile("config.xml");

	applicationData->config = new SdlApplicationData::WindowConfig(applicationData, config);
	applicationData->config->log = &log;
	SdlApplicationData::DisplayMode resolution = applicationData->config->getResolution();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		log << "SDL_Init Error: " << SDL_GetError() << '\n';

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initialization failure", "Check the error log for more details", NULL);
		throw std::runtime_error("SDL initialization failure");
	}

	applicationData->window = SDL_CreateWindow("sdl_window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution.w, resolution.h, 0);
	if (applicationData->window == nullptr) {
		log << "SDL_CreateWindow Error: " << SDL_GetError() << '\n';

		SDL_Quit();

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initialization failure", "Check the error log for more details", NULL);
		throw std::runtime_error("SDL initialization failure");
	}

	applicationData->config->updateResolutions();

	applicationData->renderer = SDL_CreateRenderer(applicationData->window, -1, SDL_RENDERER_ACCELERATED | (applicationData->config->getVsync() ? SDL_RENDERER_PRESENTVSYNC : 0));
	if (applicationData->renderer == nullptr) {
		log << "SDL_CreateRenderer Error: " << SDL_GetError() << '\n';

		SDL_DestroyWindow(applicationData->window);
		SDL_Quit();

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initialization failure", "Check the error log for more details", applicationData->window);
		throw std::runtime_error("SDL initialization failure");
	}

	log << "SDL initialized properly" << '\n';

	applicationData->config->setFullscreen(applicationData->config->getFullscreen());



	if (IMG_Init(IMAGE_TYPES) != IMAGE_TYPES) { // IMG_Init returns the flags for successfully initalized image libraries
		log << "SDL_IMG_Init Error : " << IMG_GetError() << '\n';
		IMG_Quit();

		SDL_DestroyRenderer(applicationData->renderer);
		SDL_DestroyWindow(applicationData->window);
		SDL_Quit();

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL initialization failure", "Check the error log for more details", applicationData->window);
		throw std::runtime_error("SDL initialization failure");
	}

	log << "SDL_Image initialized properly" << '\n';


	return applicationData;
}

void closeSdl(SdlApplicationData* applicationData) {
	IMG_Quit();
	SDL_DestroyRenderer(applicationData->renderer);
	SDL_DestroyWindow(applicationData->window);
	SDL_Quit();
	delete applicationData->config;
	delete applicationData;
}

tinyxml2::XMLElement* verifiedXmlElement(tinyxml2::XMLDocument* root, tinyxml2::XMLNode* node, const char* name) {
	tinyxml2::XMLElement* element = node->LastChildElement(name);
	if (element == nullptr) {
		element = root->NewElement(name);
		node->InsertEndChild(element);
	}

	return element;
}

tinyxml2::XMLElement* verifiedXmlElement(tinyxml2::XMLDocument* root, tinyxml2::XMLNode* node, std::forward_list<const char*>::iterator i, std::forward_list<const char*>::iterator end) {
	tinyxml2::XMLElement* element = node->LastChildElement(*i);
	if (element == nullptr) {
		element = root->NewElement(*i);
		node->InsertEndChild(element);
	}

	if (std::next(i, 1) == end)
		return element;
	else
		return verifiedXmlElement(root, element, std::next(i, 1), end);
}

SdlApplicationData::WindowConfig::WindowConfig(SdlApplicationData* data, tinyxml2::XMLDocument* config) : data_(data), config_(config), vsync_(true), fullscreen_(false), mode_({ 640, 480}) {
	std::forward_list<const char*> names = { "Config", "Window" };
	tinyxml2::XMLElement* window = verifiedXmlElement(config_, config_, names.begin(), names.end());
	tinyxml2::XMLElement* element;
	
	element = verifiedXmlElement(config_, window, "Vsync");
	element->QueryBoolText(&vsync_);

	element = verifiedXmlElement(config_, window, "Fullscreen");
	element->QueryBoolText(&fullscreen_);

	element = verifiedXmlElement(config_, window, "Resolution");
	element->QueryIntAttribute("x", &mode_.w);
	element->QueryIntAttribute("y", &mode_.h);
}

SdlApplicationData::WindowConfig::~WindowConfig() {
	saveConfig();
	delete config_;
}

void SdlApplicationData::WindowConfig::saveConfig() {
	tinyxml2::XMLElement* window = config_->LastChildElement("Config")->LastChildElement("Window");

	window->LastChildElement("Vsync")->SetText(vsync_);
	window->LastChildElement("Fullscreen")->SetText(fullscreen_);

	tinyxml2::XMLElement* resolution = window->LastChildElement("Resolution");
	resolution->SetAttribute("x", mode_.w);
	resolution->SetAttribute("y", mode_.h);

	config_->SaveFile("config.xml");
}

void SdlApplicationData::WindowConfig::updateResolutions() {
	int numModes = SDL_GetNumDisplayModes(0);
	modes_.clear();

	if (numModes >= 1) {
		SDL_DisplayMode mode;
		for (int i = 0; i < numModes; i++) {
			if (SDL_GetDisplayMode(0, i, &mode) != 0) {
				(*log) << "Unable to get display mode " << i << "\nSDL_Error: " << SDL_GetError() << "\n";
				break;
			}
			else {
				if ((SDL_BITSPERPIXEL(mode.format) == 24) || (SDL_BITSPERPIXEL(mode.format) == 32)) {
					bool alreadyExists = false;
					for (auto x : modes_)
						if (mode.w == x.w && mode.h == x.h) {
							alreadyExists = true;
							break;
						}
					if (!alreadyExists) {
						modes_.push_back(DisplayMode{ mode.w, mode.h });
						(*log) << "New supported mode added: " << mode.w << " x " << mode.h << "\n";
					}
				}
			}
		}
	}
	else {
		(*log) << "Unable to get number of display modes\nSDL_Error: " << SDL_GetError() << "\n";
	}
}

void SdlApplicationData::WindowConfig::setVsync(bool vsync) {
	vsync_ = vsync;
	SDL_GL_SetSwapInterval(static_cast<int>(vsync));

	(*log) << "Vsync has been " << (vsync ? "enabled" : "disabled") << "\nChanges won't be applied until restart\n";
	/*SDL_DestroyRenderer(data_->renderer);
	data_->renderer = SDL_CreateRenderer(data_->window, -1, SDL_RENDERER_ACCELERATED | (vsync ? SDL_RENDERER_PRESENTVSYNC : 0));*/
}

void SdlApplicationData::WindowConfig::setFullscreen(bool fullscreen) {
	if (!fullscreen) {
		SDL_SetWindowFullscreen(data_->window, 0);
		fullscreen_ = fullscreen;
		return;
	}
	else {
		for (auto x : modes_)
			if (mode_.w == x.w && mode_.h == x.h) {
				SDL_SetWindowFullscreen(data_->window, SDL_WINDOW_FULLSCREEN);
				fullscreen_ = fullscreen;
				return;
			}
	}

	(*log) << "Fullscreen mode " << mode_.w << " x " << mode_.h << " not supported\n";
}

bool SdlApplicationData::WindowConfig::getVsync() {
	return vsync_;
}

bool SdlApplicationData::WindowConfig::getFullscreen() {
	return fullscreen_;
}

SdlApplicationData::DisplayMode SdlApplicationData::WindowConfig::getResolution() {
	return mode_;
}
