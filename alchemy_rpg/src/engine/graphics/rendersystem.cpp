#include "rendersystem.h"

SharedRenderComponent RenderSystem::registerComponent(SharedRenderComponent component) {
	for (auto i = components_.begin(); i != components_.end(); i++)
		if (*i == component)
			return component;
	components_.push_back(SharedRenderComponent(component));

	return component;
}

void RenderSystem::unregisterComponent(const SharedRenderComponent& component) {
	for (auto i = components_.begin(); i != components_.end(); i++)
		if (*i == component)
			components_.erase(i);
}

void RenderSystem::render(SDL_Renderer* renderer) {
	for (auto i : components_)
		if (i->getParent() == nullptr)
			render(renderer, i);
}

void RenderSystem::render(SDL_Renderer* renderer, const SharedRenderComponent& component) {
	State topState(statestack_.front());

	Transform transform = component->getTransform();
	topState.transform.offset += (transform.offset * topState.transform.scale);
	topState.transform.scale *= transform.scale;

	statestack_.push_front(topState);
	rect_.x = static_cast<int>(topState.transform.offset.x);
	rect_.y = static_cast<int>(topState.transform.offset.y);

	if (component->getTexture() != nullptr) {
		std::pair<int, int> size = component->getSize();
		rect_.w = static_cast<int>(topState.transform.scale.x * static_cast<double>(size.first));
		rect_.h = static_cast<int>(topState.transform.scale.y * static_cast<double>(size.second));

		SDL_RenderCopy(renderer, component->getTexture()->getTextureHandle(), component->getSourceRect(), &rect_);
	}

	for (auto i : component->children_)
		render(renderer, i);

	statestack_.pop_front();
}