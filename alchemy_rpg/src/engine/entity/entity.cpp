#include "entity.h"

using namespace Engine;

void Entity::addComponent(SharedComponent component) {
	Id id = component->getId();

	if (removeComponent(id))
		Log("Component in entity already exists; existing component deleted", LogLevel::LOG_DEBUG, SystemName::SYSTEM_ENTITY);

	components_.emplace(std::make_pair(id, SharedComponent(component)));
}

bool Entity::removeComponent(Id id) {
	auto i = components_.find(id);
	if (i != components_.end()) {
		components_.erase(i);
		return true;
	}

	return false;
}

void Entity::dispatchMessage(BaseMessage& msg) {
	for (auto i : components_)
		i.second->receiveMessage(msg);
}

WeakComponent Entity::getComponent(Id id) {
	auto i = components_.find(id);
	if (i == components_.end())
		return WeakComponent();

	return WeakComponent(i->second);
}
