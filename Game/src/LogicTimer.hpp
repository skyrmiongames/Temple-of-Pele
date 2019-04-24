#include "LogicComponents.h"

/*
 * Created by Stuart Irwin on 4/19/2019.
 * Basic logic gates
 */

class LogicTimer : public LogicSender, public Node {
private:
	double nextTime = 0;
	double delay;
	bool single;

public:
	//Set up base timer
	LogicTimer(double delay, bool single=false) {
		this->delay = delay;
		this->single = single;
	}

	//Start new timer
	void activate() {
		nextTime = -1;
	}

	UseAmount is_singleton() {
		return single ? SINGLE : MULTI;
	}

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
				set_delete();
		}
	}
};