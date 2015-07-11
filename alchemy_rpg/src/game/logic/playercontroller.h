#ifndef game_logic_playercontroller_h
#define game_logic_playercontroller_h

#include "../../engine/engine.h"

class PlayerController : public LogicComponent {
public:
	enum class Direction {
		UP, DOWN, LEFT, RIGHT, NONE
	};

	PlayerController() :
		walkspeed(6.0), position_(), horizontal_(Direction::NONE), vertical_(Direction::NONE)
	{};

	void setWalking(Direction direction, bool state);

	virtual void handleMessage(const Message& message) override;
	virtual void updateLogic() override;
	
	double walkspeed;

private:
	Vector2D position_;
	Direction horizontal_;
	Direction vertical_;
};

#endif
