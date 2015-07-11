#include "actor.h"

void Actor::addComponent(SharedComponent component) {
	if (findOneBeforeComponent(component) == components_.end()) {
		components_.push_front(component);
		component->owner_ = this;
	}
}

void Actor::removeComponent(const SharedComponent& component) {
	auto i = findOneBeforeComponent(component);
	if (i != components_.end()) {
		components_.erase_after(i);
		(*i)->owner_ = nullptr;
	}
}

void Actor::propagateMessage(const Message& message) {
	for (auto i : components_)
		if (i->getType() != message.ignoredtype)
			i->handleMessage(message);
}

std::forward_list<std::shared_ptr<Component> >::iterator Actor::findOneBeforeComponent(const SharedComponent& component) {
	auto i = components_.begin();
	auto j = components_.before_begin();

	for (; i != components_.end(); i++) {
		if (*i == component)
			return j;
		j++;
	}
	return components_.end();
}
