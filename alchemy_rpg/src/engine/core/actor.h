#ifndef engine_core_actor_h
#define engine_core_actor_h

#include <forward_list>
#include <memory>
#include <typeinfo>

#include "component.h"
#include "message.h"

class Actor {
public:
	void addComponent(SharedComponent component);
	void removeComponent(const SharedComponent& component);
	void propagateMessage(const Message& message);


	template <class T> std::shared_ptr<T> findComponent() {
		for (auto i : components_)
			if (i != nullptr)
				if (i->getType() == T::getStaticType()) 
					return std::static_pointer_cast<T>(i);
		return std::shared_ptr<T>();
	}

private:
	std::forward_list<SharedComponent> components_;

	std::forward_list<SharedComponent>::iterator findOneBeforeComponent(const SharedComponent& component);
};

#endif