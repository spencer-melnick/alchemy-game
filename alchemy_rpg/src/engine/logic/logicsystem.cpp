#include "logicsystem.h"

SharedLogicComponent LogicSystem::registerComponent(SharedLogicComponent component) {
	for (auto i = components_.begin(); i != components_.end(); i++)
		if (*i == component)
			return component;
	components_.push_back(SharedLogicComponent(component));

	return component;
}

void LogicSystem::unregisterComponent(const SharedLogicComponent& component) {
	for (auto i = components_.begin(); i != components_.end(); i++)
		if (*i == component)
			components_.erase(i);
}

void LogicSystem::updateLogic() {
	for (auto i : components_)
		i->updateLogic();
}
