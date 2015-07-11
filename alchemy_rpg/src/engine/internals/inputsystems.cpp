#include "inputSystems.h"

void InputController::registerControl(InputMessage type, std::function<void(void)> control) {
	functions_[type] = control;
}

void InputController::registerControl(std::string name, std::function<void(bool)> control) {
	registerControl(std::make_pair(name, true), std::bind(control, true));
	registerControl(std::make_pair(name, false), std::bind(control, false));
}

void InputController::unregisterControl(InputMessage type) {
	functions_.erase(type);
}

void InputController::handleInput(InputMessage event) {
	auto i = functions_.find(event);
	if (i != std::end(functions_))
		if (i->second)
			i->second();
}



void InputDispatcher::registerController(InputController* controller) {
	controllers_.remove(controller);
	controllers_.push_back(controller);
}

void InputDispatcher::unregisterController(InputController* controller) {
	controllers_.remove(controller);
}


void InputDispatcher::mapKey(InputCode code, std::string name) {
	controlMap_[code] = name;
}

void InputDispatcher::mapKey(std::initializer_list<InputCode> code, std::string name) {
	for (InputCode i : code) {
		controlMap_[i] = name;
	}
}

void InputDispatcher::unmapKey(InputCode code) {
	controlMap_.erase(code);
}



void InputDispatcher::dispatchInput(SDL_Event event) {
	InputMessage message;
	InputCode code;
	bool active;

	switch (event.type) {
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		code = Translator::codeFromScancode(event.key.keysym.sym);
		break;
	default:
		return;
	}

	switch (event.type) {
	case SDL_KEYDOWN:
		active = true;
		break;
	case SDL_KEYUP:
		active = false;
		break;
	default:
		return;
	}

	auto i = controlMap_.find(code);
	if (i != std::end(controlMap_)) 
		for (auto j : controllers_)  
			j->handleInput(std::make_pair(i->second, active));
}

InputCode InputDispatcher::Translator::codeFromScancode(SDL_Keycode event) {
	auto i = keymap_.find(event);
	if (i != std::end(keymap_))
		return i->second;

	return InputCode::INPUT_NO_CODE;
}

std::map<SDL_Keycode, InputCode> InputDispatcher::Translator::keymap_ = { 
	{ SDLK_a, InputCode::INPUT_KEY_A }, { SDLK_b, InputCode::INPUT_KEY_B }, { SDLK_c, InputCode::INPUT_KEY_C }, { SDLK_d, InputCode::INPUT_KEY_D },
	{ SDLK_e, InputCode::INPUT_KEY_E }, { SDLK_f, InputCode::INPUT_KEY_F }, { SDLK_g, InputCode::INPUT_KEY_G }, { SDLK_h, InputCode::INPUT_KEY_H },
	{ SDLK_i, InputCode::INPUT_KEY_I }, { SDLK_j, InputCode::INPUT_KEY_J }, { SDLK_k, InputCode::INPUT_KEY_K }, { SDLK_l, InputCode::INPUT_KEY_L },
	{ SDLK_m, InputCode::INPUT_KEY_M }, { SDLK_n, InputCode::INPUT_KEY_N }, { SDLK_o, InputCode::INPUT_KEY_O }, { SDLK_p, InputCode::INPUT_KEY_P },
	{ SDLK_q, InputCode::INPUT_KEY_Q }, { SDLK_r, InputCode::INPUT_KEY_R }, { SDLK_s, InputCode::INPUT_KEY_S }, { SDLK_t, InputCode::INPUT_KEY_T },
	{ SDLK_u, InputCode::INPUT_KEY_U }, { SDLK_v, InputCode::INPUT_KEY_V }, { SDLK_w, InputCode::INPUT_KEY_W }, { SDLK_x, InputCode::INPUT_KEY_X },
	{ SDLK_y, InputCode::INPUT_KEY_Y }, { SDLK_z, InputCode::INPUT_KEY_Z }, { SDLK_ESCAPE, InputCode::INPUT_KEY_ESCAPE },
	{ SDLK_UP, InputCode::INPUT_KEY_UP }, { SDLK_DOWN, InputCode::INPUT_KEY_DOWN }, { SDLK_LEFT, InputCode::INPUT_KEY_LEFT },
	{ SDLK_RIGHT, InputCode::INPUT_KEY_RIGHT }
};

