#include "rendercomponent.h"

RenderComponent::~RenderComponent() {
	SharedRenderComponent tparent = parent_.lock();
	if (tparent != nullptr)
		tparent->removeChild(shared_from_this());
	
	for (auto i : children_) {
		if (i != nullptr)
			i->setParent(SharedRenderComponent());
	}
	children_.clear();
}

void RenderComponent::addChild(SharedRenderComponent component) {
	SharedRenderComponent parent = component->getParent();

	if (parent != nullptr)
		parent->removeChild(component);

	children_.push_front(SharedRenderComponent(component));
	component->setParent(shared_from_this());
}

void RenderComponent::removeChild(SharedRenderComponent& component) {
	auto i = children_.begin();
	auto j = children_.before_begin();

	for (; i != children_.end(); i++) {
		if (*i == component) {
			(*i)->setParent(SharedRenderComponent());
			children_.erase_after(j);
			break;
		}
		j++;
	}
}

void RenderComponent::setTransform(Transform transform) {
	transform_ = transform;
}

Transform RenderComponent::getTransform() {
	return transform_;
}


void RenderComponent::handleMessage(const Message& message) {
	if (message.type == Message::SetParent::getStaticType()) {
		auto tmessage = static_cast<const Message::SetParent&>(message);
		SharedRenderComponent parent = tmessage.owner->findComponent<RenderComponent>();

		if (parent != nullptr)
			setParent(shared_from_this());
	}
	
	if (message.type == Message::SetPosition::getStaticType())
	{
		auto tmessage = static_cast<const Message::SetPosition&>(message);
		transform_.offset = tmessage.position;
	}

	handleRenderMessage(message);
}


SharedRenderComponent RenderComponent::getParent() {
	return parent_.lock();
}

void RenderComponent::setParent(const SharedRenderComponent& component) {
	parent_ = component;
}