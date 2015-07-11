#ifndef component_h
#define component_h

#include <string>
#include <memory>

#include "message.h"

class Actor;
class Component;

using SharedComponent = std::shared_ptr<Component>;

struct Message;

class Component {
	friend class Actor;
public:
	Component() :
		type_(0), owner_(nullptr)
	{};

	virtual void handleMessage(const Message&) = 0;
	void messageOwner(Message& message);

	size_t getType() {
		return type_;
	}

	Actor* getOwner() {
		return owner_;
	}

protected:
	size_t type_;
	Actor* owner_;
};

template <typename T>
class DerivedComponent: public Component {
public:
	DerivedComponent() {
		type_ = getStaticType();
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
bool DerivedComponent<T>::typed_ = false;
template <typename T>
size_t DerivedComponent<T>::statictype_ = 0;

#endif