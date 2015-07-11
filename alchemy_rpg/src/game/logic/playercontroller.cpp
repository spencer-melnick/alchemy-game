#include "playercontroller.h"

#include <iostream>

void PlayerController::setWalking(Direction direction, bool state) {
	if (state == false) {
		switch (direction) {
		case Direction::LEFT:
		case Direction::RIGHT:
			if (horizontal_ == direction)
				horizontal_ = Direction::NONE;
			break;
		case Direction::UP:
		case Direction::DOWN:
			if (vertical_ == direction)
				vertical_ = Direction::NONE;
			break;
		default:
			break;
		}
	}
	else if (state == true) {
		switch (direction) {
		case Direction::LEFT:
		case Direction::RIGHT:
			horizontal_ = direction;
			break;
		case Direction::UP:
		case Direction::DOWN:
			vertical_ = direction;
			break;
		default:
			break;
		}
	}
}

void PlayerController::handleMessage(const Message& message) {
	if (message.type == Message::SetPosition::getStaticType()) {
		auto tmessage = static_cast<const Message::SetPosition&>(message);
		position_ = tmessage.position;
	}
}

void PlayerController::updateLogic() {
	Vector2D move;

	if (horizontal_ == Direction::LEFT)
		move.x = -1.0;
	else if (horizontal_ == Direction::RIGHT)
		move.x = 1.0;

	if (vertical_ == Direction::UP)
		move.y = -1.0;
	else if (vertical_ == Direction::DOWN)
		move.y = 1.0;

	position_ += (move.normalize() *= walkspeed);
	messageOwner(Message::SetPosition(position_));
}
