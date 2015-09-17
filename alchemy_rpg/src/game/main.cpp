#include <iostream>

#include "../engine/engine.h"

int main(int argc, char *argv[]) {
	Engine::Window window;
	Engine::Renderer renderer(window);

	Engine::Logger::setOutput(std::cout);
	std::ofstream log;

	log.open("log.txt");



	if (log.is_open())
		Engine::Logger::setOutput(log);

	try {

		window.create("Hello world!", 0, 0, 640, 480, 0);
		renderer.create(SDL_RENDERER_ACCELERATED);

		Engine::ResourceManager resources;
		Engine::TextureFactory textureFactory(renderer);

		resources.extensionAssociations.push_back(std::make_pair(IMAGE_EXTENSIONS, &textureFactory));
		resources.loadResource("rc/oga/Jason-Em/Old hero.png", 2);

		Engine::Texture* texture = dynamic_cast<Engine::Texture*>(resources.getResource("rc/oga/Jason-Em/Old hero.png"));

		if (texture != nullptr) {
			SDL_RenderClear(renderer.getSdlRenderer());
			SDL_RenderCopy(renderer.getSdlRenderer(), texture->getTexture(), nullptr, nullptr);
			SDL_RenderPresent(renderer.getSdlRenderer());
		}

		SDL_Delay(1000);



	}
	catch (Engine::Error& error)
	{
		std::cout << (error.fatal ? "FATAL ERROR: " : "ERROR: ") << error.what() << "\n";

		if (error.fatal) {
			window.destroy();
			return 1;
		}
	}

	window.destroy();
	log.close();
	return 0;
}