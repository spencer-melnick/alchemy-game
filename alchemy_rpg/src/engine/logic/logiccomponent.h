#ifndef engine_logic_logiccomponent_h
#define engine_logic_logiccomponent_h

#include <memory>

#include "../core/component.h"

class LogicComponent;
using SharedLogicComponent = std::shared_ptr < LogicComponent > ;

class LogicComponent : public DerivedComponent < LogicComponent > {
public:
	virtual void handleMessage(const Message& message) override {};
	virtual void updateLogic() {};
};

#endif
