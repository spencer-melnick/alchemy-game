#include "component.h"

using namespace Engine;

BaseComponent::BaseComponent(Entity& owner) 
	: owner_(owner) {};

Entity& BaseComponent::getOwner() {
	return owner_;
}
