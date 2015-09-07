#pragma once

#include <memory>

#include "../core/type.h"
#include "message.h"

namespace Engine
{
	class Entity;

	class BaseComponent {
	public:
		BaseComponent(Entity& owner);

		virtual void receiveMessage(BaseMessage& msg) = 0;
		virtual Id getId() = 0;
		Entity& getOwner();

	private:
		Entity& owner_;
	};

	template <typename T>
	class Component : public BaseComponent {
	public:
		Component(Entity& owner)
			: BaseComponent(owner) {};

		Id static getStaticId() {
			return Type<BaseComponent, T>::getId();
		}

		virtual Id getId() {
			return getStaticId();
		}
	};

	template <typename T>
	using ComponentType = Type<BaseComponent, T>;
	
	using SharedComponent = std::shared_ptr<BaseComponent>;
	using WeakComponent = std::weak_ptr<BaseComponent>;
}
