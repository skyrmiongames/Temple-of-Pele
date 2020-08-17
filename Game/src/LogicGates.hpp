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
	bool running = false;

public:
	//Set up base timer
	LogicTimer(unsigned char layer, double delay, bool single=false) : Node(layer) {
		this->delay = delay;
		this->single = single;
	}

	//Start new timer
	void activate() {
		running = true;
		nextTime = delay;
	}

	RecivingAction getRecivingAction() { return single ? SETDELETE : NONE; };

	//Wait for end of timer
	void update(double time) {
		//Set timer
		if(running && (nextTime -= time) <= 0) {
			//Finish timer
			running = false;
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