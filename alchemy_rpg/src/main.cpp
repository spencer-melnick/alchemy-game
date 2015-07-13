#include <iostream>
#include <functional>

#include <SDL.h>

#include "engine/engine.h"

#include "game/logic/playercontroller.h"

int main(int, char**) {
	SdlApplicationData* applicationData = initializeSdl(std::cout);
	InputDispatcher mainDispatch;
	InputController windowController;
	InputController playerController;

	TextureFactory textureFactory(applicationData->renderer);
	SDL_Texture* texture1 = textureFactory.loadTexture("rc/oga/Jason-Em/Old hero.png", std::cout);

	bool running = true;

	mainDispatch.registerController(&windowController);
	mainDispatch.registerController(&playerController);
	windowController.registerControl(std::make_pair("ExitKey", true), [&running](){ running = false; });
	windowController.registerControl(std::make_pair("FullscreenKey", true), [&applicationData]{ applicationData->config->setFullscreen(!applicationData->config->getFullscreen()); });
	mainDispatch.mapKey(InputCode::INPUT_KEY_ESCAPE, "ExitKey");
	mainDispatch.mapKey(InputCode::INPUT_KEY_V, "FullscreenKey");

	mainDispatch.mapKey(InputCode::INPUT_KEY_LEFT, "Left");
	mainDispatch.mapKey(InputCode::INPUT_KEY_RIGHT, "Right");
	mainDispatch.mapKey(InputCode::INPUT_KEY_UP, "Up");
	mainDispatch.mapKey(InputCode::INPUT_KEY_DOWN, "Down");

	SDL_Event event;


	RenderSystem mainRendering;
	LogicSystem mainLogic;

	Actor guy;
	std::shared_ptr<PlayerController> controller(new PlayerController());
	guy.addComponent(mainRendering.registerComponent(SharedRenderComponent(new Sprite(texture1))));
	guy.addComponent(mainLogic.registerComponent(controller));
	guy.propagateMessage(Message::SetPosition(Vector2D(128.0, 64.0)));

	playerController.registerControl("Left", [&controller](bool state){ controller->setWalking(PlayerController::Direction::LEFT, state); });
	playerController.registerControl("Right", [&controller](bool state){ controller->setWalking(PlayerController::Direction::RIGHT, state); });
	playerController.registerControl("Up", [&controller](bool state){ controller->setWalking(PlayerController::Direction::UP, state); });
	playerController.registerControl("Down", [&controller](bool state){ controller->setWalking(PlayerController::Direction::DOWN, state); });


	while (running) {
		mainLogic.updateLogic();

		SDL_RenderClear(applicationData->renderer);
		mainRendering.render(applicationData->renderer);
		SDL_RenderPresent(applicationData->renderer);

		while (SDL_PollEvent(&event))
			mainDispatch.dispatchInput(event);
	}

	textureFactory.unloadTextures();
	closeSdl(applicationData);

	return 0;
}