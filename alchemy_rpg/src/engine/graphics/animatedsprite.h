#ifndef engine_graphics_animatedsprite_h
#define engine_graphics_animatedsprite_h

#include <map>
#include <utility>
#include <vector>
#include <string>
#include <cmath>

#include <SDL.h>

#include "rendercomponent.h"
#include "sprite.h"

//TODO: add animation loading system and frame increments
//note- possibly add messages to individual frames of animations to be processed by logic component?
//sync animations with character functions
//i.e. frame 4 of animation "attack" sends message to logic to process potential hit events
//or last frame of animation ends animation and switches to another (maybe just add flag for animation not to loop?,
//or some specific value of different animation to cut to?

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(AnimatedTexture& texture);

protected:
	std::pair<unsigned char, unsigned char> currentframe_;
	std::vector<std::vector<SDL_Rect> > frames_; //possibly change to another container - construct from vector
};

#endif
