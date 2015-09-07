#pragma once

#include "../core/type.h"

namespace Engine
{

	class BaseMessage {
	public:
		virtual Id getId() = 0;
		bool isA(Id object);
	};

	template <typename T>
	class Message: public BaseMessage {
	public:
		Id static getStaticId() {
			return Type<BaseMessage, T>::getId();
		}

		virtual Id getId() override {
			return getStaticId();
		}
	};

	template <typename T>
	using MessageType = Type<BaseMessage, T>;

}
