#ifndef engine_internals_texture_factory_h
#define engine_internals_texture_factory_h

#include <forward_list>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

class TextureFactory;

struct Animation {
	std::vector<std::pair<unsigned int, unsigned int> > frames;
	double frametime;
};

class Texture {
	friend class TextureFactory;
public:
	virtual SDL_Texture* getTextureHandle() {
		return texture_;
	}

	virtual const std::string& getFilename() {
		return filename_;
	}

	virtual const bool getIsAnimated() {
		return false;
	}

	virtual const std::map<std::string, Animation>& getAnimations() {
		return emptyanimation_;
	}

protected:
	Texture(SDL_Texture* texture, std::string filename) : texture_(texture), filename_(filename)
		{};

	enum class TextureType {
		TEXTURE_STATIC,
		TEXTURE_ANIMATED
	};

	SDL_Texture* texture_;
	std::string filename_;

	virtual const TextureType getInternalType() {
		return TextureType::TEXTURE_STATIC;
	}

private:
	std::map<std::string, Animation> emptyanimation_;
};

class AnimatedTexture : public Texture {
	friend class TextureFactory;
public:
	struct SpriteConfig {
		unsigned int imageWidth, imageHeight,
			paddingX, paddingY,
			spaceX, spaceY,
			frameWidth, frameHeight;
		std::map<std::string, Animation> animations;
	};

	virtual const std::map<std::string, Animation>& getAnimations() override {
		return animations_;
	}

	virtual const bool getIsAnimated() override {
		return true;
	}

protected:
	AnimatedTexture(SDL_Texture* texture, std::string filename, SpriteConfig config,
		const std::map<std::string, Animation>& animations);

	std::map<std::string, Animation> animations_;
	std::vector<std::vector<SDL_Rect> > frames_;

	virtual const TextureType getInternalType() {
		return TextureType::TEXTURE_ANIMATED;
	}
};

class TextureFactory {
public:
	TextureFactory(SDL_Renderer* renderer) :
		renderer_(renderer)
	{};

	Texture* loadStaticTexture(std::string filename, std::ostream& log) {
		return loadTexture(filename, log);
	}

	AnimatedTexture* loadAnimatedTexture(std::string filename, AnimatedTexture::SpriteConfig& config,
		std::ostream& log, std::map<std::string, Animation>& animations)
	{
		return static_cast<AnimatedTexture*>(loadTexture(filename, log, &config));
	}
	void reloadTextures(std::ostream& log);
	void unloadTextures();

protected:
	Texture* loadTexture(std::string filename, std::ostream& log,
		AnimatedTexture::SpriteConfig* config = nullptr, std::map<std::string, Animation>* animations = nullptr);
	SDL_Texture* loadTextureData(std::string filename, std::ostream& log);

private:
	SDL_Renderer* renderer_;
	SDL_Surface* loadingSurface_;
	std::forward_list<Texture> textures_;
};

#endif