#pragma once

#ifndef Python_Interpreter_Support_FlowControl
#define Python_Interpreter_Support_FlowControl

#include "claim.hpp"

class FlowController {
public:
	enum class FlowState: u8 {
		ACTIVE	= 0b001,
		NEXT	= 0b010,
		EXIT	= 0b100,
	};

private:
	std::stack<FlowState> states;

public:
	void activate() {  states.top() = FlowState::ACTIVE; }
	void nextloop() { states.top() = FlowState::NEXT; }
	void breakout() { states.top() = FlowState::EXIT; }
	void exit() { states.top() = FlowState::EXIT; }

	bool active() const { return states.top() == FlowState::ACTIVE; }
	bool exited() const { return states.top() == FlowState::EXIT; }

	void newScope() { states.push(FlowState::ACTIVE); }
	void delScope() { states.pop(); }
};

#endif
