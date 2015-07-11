#include "component.h"
#include "actor.h"

void Component::messageOwner(Message& message) {
	if (owner_ != nullptr) {
		message.ignoredtype = type_;
		owner_->propagateMessage(message);
	}
}