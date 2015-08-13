#ifndef engine_graphics_sprite_h
#define engine_graphics_sprite_h

#include <SDL.h>

#include "rendercomponent.h"

class Sprite : public RenderComponent { //not a finished class, just to test the rendering entity-component system
public:
	Sprite(Texture* texture) :
		texture_(texture)
	{};

	Texture* getTexture() {
		return texture_;
	}

protected:
	Texture* texture_;
};

#endif