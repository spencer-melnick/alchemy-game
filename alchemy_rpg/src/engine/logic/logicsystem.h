#ifndef engine_logic_logicsystem_h
#define engine_logic_logicsystem_h

#include <list>

#include "logiccomponent.h"

class LogicSystem {
public:
	SharedLogicComponent registerComponent(SharedLogicComponent component);
	void unregisterComponent(const SharedLogicComponent& component);
	void updateLogic();

private:
	std::list<SharedLogicComponent> components_;
};

#endif
