#include "message.h"

using namespace Engine;

bool BaseMessage::isA(Id object) {
	return (getId() == object);
}
