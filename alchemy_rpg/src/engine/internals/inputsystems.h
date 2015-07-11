#ifndef engine_internals_input_systems_h
#define engine_internals_input_systems_h

#include <functional>
#include <list>
#include <initializer_list>
#include <map>

#include <SDL.h>

using InputMessage = std::pair < std::string, bool > ;

enum class InputCode {
	INPUT_KEY_A, INPUT_KEY_B, INPUT_KEY_C, INPUT_KEY_D, INPUT_KEY_E, INPUT_KEY_F,
	INPUT_KEY_G, INPUT_KEY_H, INPUT_KEY_I, INPUT_KEY_J, INPUT_KEY_K, INPUT_KEY_L,
	INPUT_KEY_M, INPUT_KEY_N, INPUT_KEY_O, INPUT_KEY_P, INPUT_KEY_Q, INPUT_KEY_R,
	INPUT_KEY_S, INPUT_KEY_T, INPUT_KEY_U, INPUT_KEY_V, INPUT_KEY_W, INPUT_KEY_X,
	INPUT_KEY_Y, INPUT_KEY_Z, INPUT_KEY_ESCAPE, INPUT_KEY_UP, INPUT_KEY_DOWN,
	INPUT_KEY_LEFT, INPUT_KEY_RIGHT, INPUT_NO_CODE
};

class InputController {
public:
	void registerControl(InputMessage type, std::function<void(void)> control);
	void registerControl(std::string name, std::function<void(bool)> control);
	void unregisterControl(InputMessage type);
	void handleInput(InputMessage event);

private:
	std::map<InputMessage, std::function<void()> > functions_;
};

class InputDispatcher {
public:
	void registerController(InputController* controller);
	void unregisterController(InputController* controller);

	void mapKey(InputCode code, std::string name);
	void mapKey(std::initializer_list<InputCode> code, std::string name);
	void unmapKey(InputCode code);

	void dispatchInput(SDL_Event event);

private:
	class Translator {
	public:
		static InputCode codeFromScancode(SDL_Keycode code);

	private:
		static std::map<SDL_Keycode, InputCode> keymap_;
	};


	std::list<InputController*> controllers_;
	std::map<InputCode, std::string> controlMap_;
};




#endif
