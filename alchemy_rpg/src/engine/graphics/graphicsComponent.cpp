#include "graphicsComponent.h"

using namespace Engine;

GraphicsComponent::GraphicsComponent(Entity & owner)
	: Component(owner) {}

void GraphicsComponent::receiveMessage(BaseMessage & message) {
}
