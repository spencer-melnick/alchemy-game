#pragma once

#include <map>
#include <memory>

#include "../core/log.h"
#include "message.h"
#include "component.h"
#include "node.h"

namespace Engine
{

	class Entity: public Node<Entity> {
	public:
		void addComponent(SharedComponent component);
		bool removeComponent(Id id);
		void dispatchMessage(BaseMessage& msg);
		WeakComponent getComponent(Id id);

	protected:
		std::map<Id, SharedComponent> components_;
	};

}
