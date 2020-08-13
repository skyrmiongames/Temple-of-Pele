#include "LogicComponents.h"

/*
 * Created by Stuart Irwin on 4/19/2019.
 * Basic logic gates
 */

class LogicTimer : public Node, public LogicDevice {
private:
	double nextTime = 0;
	double delay;
	bool single;

public:
	//Set up base timer
	LogicTimer(unsigned char layer, double delay, bool single=false) : Node(layer) {
		this->delay = delay;
		this->single = single;
	}

	//Start new timer
	void activate() {
		nextTime = -1;
	}

	RecivingAction getRecivingAction() { return single ? SETDELETE : NONE; };

	//Wait for end of timer
	void update(double time) {
		//Set timer
		if(nextTime == -1)
			nextTime = time + delay;
		else if(nextTime > 0 && time >= nextTime) {
			//Finish timer
			nextTime = 0;
			send();
			if(single)
				setDelete();
		}
	}
};

class LogicCounter : public LogicDevice {
private:
	int goal;
	int current = 0;

public:
	LogicCounter(int goal) {
		this->goal = goal;
	}

	void activate() {
		if(++current >= goal) {
			current -= goal;
			send();
		}
	}
};