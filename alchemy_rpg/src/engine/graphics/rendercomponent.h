#ifndef engine_graphics_rendercomponent_h
#define engine_graphics_rendercomponent_h

#include <memory>
#include <forward_list>
#include <string>

#include <SDL.h>

#include "../core/component.h"
#include "../core/actor.h"
#include "../internals/vector2d.h"
#include "../core/message.h"

class RenderSystem;
class RenderComponent;

using SharedRenderComponent = std::shared_ptr<RenderComponent>;

class RenderComponent : public DerivedComponent<RenderComponent>, public std::enable_shared_from_this<RenderComponent> {
	friend class RenderSystem;
public:
	~RenderComponent();

	void addChild(SharedRenderComponent component);
	void removeChild(SharedRenderComponent& component);

	void setTransform(Transform transform);
	Transform getTransform();


	virtual SDL_Texture* getTexture() {
		return nullptr;
	}
	virtual void handleMessage(const Message& message) override final;

protected:
	std::forward_list<SharedRenderComponent> children_;
	Transform transform_;

	SharedRenderComponent getParent();
	virtual void handleRenderMessage(const Message& message) {};

private:
	std::weak_ptr<RenderComponent> parent_;

	void setParent(const SharedRenderComponent& component);
};

#endif

