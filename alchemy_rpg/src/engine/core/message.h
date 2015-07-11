#ifndef engine_core_message_h
#define engine_core_message_h

#include <typeinfo>
#include "../internals/vector2d.h"

class Actor;

struct Message {
	struct SetParent;
	struct SetPosition;

	size_t type;
	size_t ignoredtype;

	Message() :
		type(0), ignoredtype(0)
	{};
};

template <typename T>
struct DerivedMessage : public Message {
	DerivedMessage() {
		type = getStaticType();
	}

	static const size_t getStaticType() {
		if (!typed_) {
			typed_ = true;
			statictype_ = typeid(T).hash_code();
		}

		return statictype_;
	}

private:
	static bool typed_;
	static size_t statictype_;
};

template <typename T>
bool DerivedMessage<T>::typed_ = false;
template <typename T>
size_t DerivedMessage<T>::statictype_ = 0;




struct Message::SetParent: public DerivedMessage<SetParent> {
	Actor* owner;
};

struct Message::SetPosition: public DerivedMessage<SetPosition>
{
	Vector2D position;

	SetPosition(Vector2D pos) :
		position(pos)
	{};
};

#endif
