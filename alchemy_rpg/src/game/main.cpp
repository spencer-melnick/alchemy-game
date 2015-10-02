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
		Engine::SpriteRenderer spriteRenderer(renderer);

		resources.extensionAssociations.push_back(std::make_pair(IMAGE_EXTENSIONS, &textureFactory));
		resources.loadResource("rc/oga/Jason-Em/Old hero.png", 2);

		Engine::Texture* texture = dynamic_cast<Engine::Texture*>(resources.getResource("rc/oga/Jason-Em/Old hero.png"));

		SDL_Rect src;
		src.w = 128;
		src.h = 112;
		src.x = 0;
		src.y = 0;

		Engine::Transform trs;
		trs.position = Engine::Vector2D(64.0, 56.0);

		Engine::Sprite* sprite = spriteRenderer.newSprite();
		sprite->setTexture(texture->getTexture());
		sprite->setSource(src);
		sprite->setSize(Engine::Vector2D(128.0, 112.0));
		sprite->setTransform(trs);

		sprite = spriteRenderer.newSprite();
		sprite->setTexture(texture->getTexture());
		sprite->setSource(src);
		sprite->setSize(Engine::Vector2D(128.0, 112.0));
		trs.position = Engine::Vector2D(100.0, 100.0);
		trs.depth = -1;
		sprite->setTransform(trs);

		if (texture != nullptr) {
			SDL_RenderClear(renderer.getSdlRenderer());
			spriteRenderer.render();
			//SDL_RenderCopy(renderer.getSdlRenderer(), texture->getTexture(), nullptr, nullptr);
			SDL_RenderPresent(renderer.getSdlRenderer());
		}

		SDL_Delay(1000);


		trs.depth = 1;
		sprite->setTransform(trs);
		if (texture != nullptr) {
			SDL_RenderClear(renderer.getSdlRenderer());
			spriteRenderer.render();
			//SDL_RenderCopy(renderer.getSdlRenderer(), texture->getTexture(), nullptr, nullptr);
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